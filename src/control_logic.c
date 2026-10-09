#include "control_logic.h"

int moisture_percent(int adc, int adc_mojado, int adc_seco) {
    if (adc_mojado < 0 || adc_mojado >= adc_seco || adc_seco > 4095 ||
        adc < 0 || adc > 4095) return -1;
    if (adc <= adc_mojado) return 100;
    if (adc >= adc_seco) return 0;
    /* Redondeo al entero más cercano para muestras ADC de 12 bits. */
    return (int)((((int64_t)adc_seco - adc) * 100 +
                  (adc_seco - adc_mojado) / 2) / (adc_seco - adc_mojado));
}

servo_state_t desired_servo_state(int humidity_pct, bool valid,
                                  servo_state_t previous,
                                  const control_config_t *cfg) {
    /* Estado seguro adoptado en esta reconstrucción ante lectura inválida. */
    if (!valid || cfg == NULL || humidity_pct < 0 || humidity_pct > 100 ||
        cfg->umbral_apertura_pct < 0 ||
        cfg->umbral_apertura_pct >= cfg->umbral_cierre_pct ||
        cfg->umbral_cierre_pct > 100) return SERVO_CERRADO;
    if (humidity_pct >= cfg->umbral_cierre_pct) return SERVO_CERRADO;
    if (humidity_pct <= cfg->umbral_apertura_pct) return SERVO_ABIERTO;
    /* Intervalo no documentado en la demostración: conservar estado válido. */
    return previous == SERVO_ABIERTO ? SERVO_ABIERTO : SERVO_CERRADO;
}

void moving_average_init(moving_average_t *f) {
    if (!f) return;
    *f = (moving_average_t){0};
}

int moving_average_add(moving_average_t *f, int sample) {
    if (!f || sample < 0 || sample > 4095) return -1;
    const size_t capacity = sizeof(f->history) / sizeof(f->history[0]);
    if (f->count == capacity) f->total -= f->history[f->next];
    else f->count++;
    f->history[f->next] = sample;
    f->total += sample;
    f->next = (f->next + 1) % capacity;
    return (int)((f->total + (int64_t)f->count / 2) / (int64_t)f->count);
}
