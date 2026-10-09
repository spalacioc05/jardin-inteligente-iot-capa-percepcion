#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H
/* ¡IMPORTANTE! Estos GPIO son EJEMPLOS para ESP32 clásico DevKit V1.
 * NO se pueden inferir los GPIO reales a partir de las fotos.
 * Confirmar la placa, sus tensiones y el cableado antes de flashear. */
#define PIN_SENSOR_ADC_CHANNEL ADC_CHANNEL_6  /* ESP32 clásico: GPIO34 */
#define PIN_SERVO_GPIO 18                     /* Suposición de referencia */
#define ADC_SECO 4095
#define ADC_MOJADO 2100
#define PCT_APERTURA 0
#define PCT_CIERRE 70
#define TOMA_MUESTRA_MS 1000
#define ESPERA_LECTURA_MS (3 * TOMA_MUESTRA_MS)
#define SERVO_PULSO_CERRADO_US 1000          /* Ajustar orientación mecánica */
#define SERVO_PULSO_ABIERTO_US 2000          /* Ajustar recorrido real */

#if ADC_MOJADO < 0 || ADC_SECO > 4095 || ADC_MOJADO >= ADC_SECO
#error "Calibracion ADC invalida: requiere 0 <= mojado < seco <= 4095"
#endif
#if PCT_APERTURA < 0 || PCT_APERTURA >= PCT_CIERRE || PCT_CIERRE > 100
#error "Umbrales invalidos: requiere 0 <= apertura < cierre <= 100"
#endif
#if TOMA_MUESTRA_MS <= 0 || ESPERA_LECTURA_MS <= TOMA_MUESTRA_MS
#error "El tiempo de espera debe superar el periodo de muestreo"
#endif
#if SERVO_PULSO_CERRADO_US <= 0 || SERVO_PULSO_CERRADO_US >= 20000 || \
    SERVO_PULSO_ABIERTO_US <= 0 || SERVO_PULSO_ABIERTO_US >= 20000
#error "Los pulsos deben estar dentro del periodo PWM de 20000 us"
#endif
#endif
