#ifndef CONTROL_LOGIC_H
#define CONTROL_LOGIC_H
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* Parámetros de una sesión de caracterización, no medidas universales. */
typedef struct {
    int adc_mojado;                 /* ADC con muestra húmeda, p.ej. 2100 */
    int adc_seco;                   /* ADC en condición seca, p.ej. 4095 */
    int umbral_cierre_pct;          /* 70 según comunicación del equipo */
    int umbral_apertura_pct;        /* 0 según comunicación del equipo */
} control_config_t;

typedef enum {
    SERVO_CERRADO = 0,
    SERVO_ABIERTO = 1
} servo_state_t;

typedef struct {
    int history[8];
    size_t count;
    size_t next;
    int64_t total;
} moving_average_t;

int moisture_percent(int adc, int adc_mojado, int adc_seco);
servo_state_t desired_servo_state(int humidity_pct, bool valid,
                                  servo_state_t previous,
                                  const control_config_t *cfg);
void moving_average_init(moving_average_t *f);
int moving_average_add(moving_average_t *f, int sample);
#endif
