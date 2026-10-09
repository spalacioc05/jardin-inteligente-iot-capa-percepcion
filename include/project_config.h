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
#define SERVO_PULSO_CERRADO_US 1000          /* Ajustar orientación mecánica */
#define SERVO_PULSO_ABIERTO_US 2000          /* Ajustar recorrido real */
#endif
