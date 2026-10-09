/*
 * Jardín inteligente: firmware de referencia para la capa de percepción.
 * ADC, media móvil y control del servo mediante tareas FreeRTOS.
 * Correspondencia con el programa de la demostración y validación física
 * pendientes; consultar docs/ESTADO_REAL.md antes de cargar en la placa.
 */
#include <stdbool.h>
#include <stdint.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "esp_adc/adc_oneshot.h"
#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "control_logic.h"
#include "project_config.h"

static const char *TAG = "plant";
static QueueHandle_t s_readings_queue;
static adc_oneshot_unit_handle_t s_adc;
static const control_config_t s_cfg = {
    .adc_mojado = ADC_MOJADO,
    .adc_seco = ADC_SECO,
    .umbral_cierre_pct = PCT_CIERRE,
    .umbral_apertura_pct = PCT_APERTURA,
};

typedef struct {
    int raw;
    int filtered;
    int humidity_pct;
    uint32_t timestamp_ms;
    bool valid;
} reading_t;

static void init_adc(void) {
    const adc_oneshot_unit_init_cfg_t init = {.unit_id = ADC_UNIT_1};
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init, &s_adc));
    const adc_oneshot_chan_cfg_t chan = {
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_12,
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(
        s_adc, PIN_SENSOR_ADC_CHANNEL, &chan));
}

static uint32_t pulse_to_duty(uint32_t pulse_us) {
    const uint32_t pwm_period_us = 20000; /* 50 Hz */
    return (pulse_us * (1U << LEDC_TIMER_16_BIT)) / pwm_period_us;
}

static void init_servo(void) {
    const ledc_timer_config_t timer = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
        .duty_resolution = LEDC_TIMER_16_BIT,
        .freq_hz = 50,
        .clk_cfg = LEDC_AUTO_CLK,
    };
    ESP_ERROR_CHECK(ledc_timer_config(&timer));
    const ledc_channel_config_t channel = {
        .gpio_num = PIN_SERVO_GPIO,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_0,
        .duty = pulse_to_duty(SERVO_PULSO_CERRADO_US),
        .hpoint = 0,
    };
    ESP_ERROR_CHECK(ledc_channel_config(&channel));
}

static void write_servo(servo_state_t state) {
    uint32_t pulse = state == SERVO_ABIERTO ?
        SERVO_PULSO_ABIERTO_US : SERVO_PULSO_CERRADO_US;
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE,
                                  LEDC_CHANNEL_0, pulse_to_duty(pulse)));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0));
}

static void acquisition_task(void *arg) {
    (void)arg;
    moving_average_t filter;
    moving_average_init(&filter);
    TickType_t last = xTaskGetTickCount();
    while (true) {
        int raw = -1;
        esp_err_t err = adc_oneshot_read(s_adc, PIN_SENSOR_ADC_CHANNEL, &raw);
        bool valid = (err == ESP_OK && raw >= 0 && raw <= 4095);
        if (!valid) {
            ESP_LOGW(TAG, "Lectura ADC invalida: %s (ADC=%d)", esp_err_to_name(err), raw);
            /* No mezclar muestras anteriores al fallo con la recuperación. */
            moving_average_init(&filter);
        }
        int filtered = valid ? moving_average_add(&filter, raw) : -1;
        int humidity_pct = valid ? moisture_percent(filtered, s_cfg.adc_mojado,
                                                    s_cfg.adc_seco) : -1;
        reading_t r = {
            .raw = raw,
            .filtered = filtered,
            .humidity_pct = humidity_pct,
            .valid = valid && humidity_pct >= 0,
            .timestamp_ms = (uint32_t)(esp_timer_get_time() / 1000ULL),
        };
        /* Mantener la lectura más reciente evita crecer memoria sin control. */
        xQueueOverwrite(s_readings_queue, &r);
        vTaskDelayUntil(&last, pdMS_TO_TICKS(TOMA_MUESTRA_MS));
    }
}

static void control_task(void *arg) {
    (void)arg;
    servo_state_t state = SERVO_CERRADO;
    reading_t r;
    while (true) {
        if (xQueueReceive(s_readings_queue, &r, pdMS_TO_TICKS(ESPERA_LECTURA_MS)) != pdTRUE) {
            state = SERVO_CERRADO;
            write_servo(state);
            ESP_LOGW(TAG, "Sin nuevas muestras: servo CERRADO");
            continue;
        }
        servo_state_t next = desired_servo_state(r.humidity_pct, r.valid, state, &s_cfg);
        if (next != state) {
            state = next;
            write_servo(state);
            ESP_LOGI(TAG, "Servo -> %s", state == SERVO_ABIERTO ? "ABIERTO" : "CERRADO");
        }
        if (!r.valid) {
            ESP_LOGW(TAG, "Humedad no disponible | servo CERRADO");
            continue;
        }
        ESP_LOGI(TAG, "Humedad: %d%% (ADC=%d | media=%d) | AUTO | servo %s | t=%lu ms",
                 r.humidity_pct, r.raw, r.filtered,
                 state == SERVO_ABIERTO ? "ABIERTO" : "CERRADO",
                 (unsigned long)r.timestamp_ms);
    }
}

void app_main(void) {
    ESP_LOGW(TAG, "FIRMWARE RECONSTRUIDO: pines y servo sin validar en hardware del equipo");
    init_adc();
    init_servo();
    s_readings_queue = xQueueCreate(1, sizeof(reading_t));
    if (!s_readings_queue) {
        ESP_LOGE(TAG, "No se pudo crear cola FreeRTOS");
        ESP_ERROR_CHECK(adc_oneshot_del_unit(s_adc));
        return;
    }
    /* El control espera en la cola antes de iniciar la adquisición. */
    TaskHandle_t control_handle = NULL;
    if (xTaskCreate(control_task, "control_servo", 4096, NULL, 4,
                    &control_handle) != pdPASS) {
        ESP_LOGE(TAG, "No se pudo crear tarea de control");
        vQueueDelete(s_readings_queue);
        ESP_ERROR_CHECK(adc_oneshot_del_unit(s_adc));
        return;
    }
    if (xTaskCreate(acquisition_task, "adquisicion_ADC", 4096, NULL, 5, NULL) != pdPASS) {
        ESP_LOGE(TAG, "No se pudo crear tarea de adquisicion");
        vTaskDelete(control_handle);
        vQueueDelete(s_readings_queue);
        ESP_ERROR_CHECK(adc_oneshot_del_unit(s_adc));
        write_servo(SERVO_CERRADO);
    }
}
