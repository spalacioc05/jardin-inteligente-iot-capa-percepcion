# Pruebas y validación

## Registros de la experiencia

| ID | Prueba u observación | Evidencia | Alcance |
|---|---|---|---|
| P-01 | ADC seco de 4095 y humedad del 0 % | E01, E06 | Visible en capturas. |
| P-02 | Lecturas húmedas próximas a 2064–2100 y 100 % | E03, E09 | Valores de las sesiones de caracterización. |
| P-03 | Variaciones del porcentaje | E09, E11 | Registros durante cambios de humedad. |
| P-04 | Estados abierto y cerrado del servo | E18–E20 y descripción del equipo | Demostración del riego simulado. |
| P-05 | Bomba controlada mediante relé | E12: componente aislado | Sin integración funcional. |
| P-06 | Nivel de tanque con HC-SR04 | E13: componente aislado | Sin integración funcional. |
| P-07 | DHT11 y comunicaciones de red | Sin registros | Sin integración demostrada. |
| P-08 | FreeRTOS y ESP-IDF en el programa original | PlatformIO visible en consola | No verificable sin el código original. |

Las imágenes están disponibles en el [catálogo](EVIDENCIAS.md).

## Verificaciones del repositorio

En la revisión de octubre de 2026 se ejecutaron las pruebas nativas con GCC y GNU Make para Windows (`mingw32-make -C tests test CC=gcc`). La compilación empleó C11, `-Wall -Wextra -Werror -pedantic` y optimización `-O2`: **resultado satisfactorio**.

Los casos de [test_control_logic.c](../tests/test_control_logic.c) cubren extremos y redondeo de calibración, rangos ADC inválidos, umbrales de apertura/cierre, conservación del estado, configuraciones inválidas, arranque del filtro, sustitución de muestras y reinicio de su ventana.

El script `python scripts/verificar_evidencias.py` comprueba las 20 imágenes PNG, identificadores y rutas únicos, correspondencia con el directorio de fotos y referencias del catálogo. **Resultado satisfactorio**.

También se comprobaron los enlaces locales y sus anclas, la correspondencia del catálogo con el inventario, el XML de la portada SVG y el renderizado de los cinco bloques Mermaid. Las 20 fotografías conservaron exactamente los mismos bytes que la versión anterior del repositorio.

Estas pruebas se ejecutan en PC. No verifican ADC físico, PWM, temporización ni tareas FreeRTOS. **PlatformIO no está instalado en el entorno de revisión**, por lo que no se ejecutó la compilación del firmware.

## Validaciones pendientes

- [ ] Compilar con `pio run -e esp32doit-devkit-v1`.
- [ ] Confirmar referencia de la placa, GPIO, niveles eléctricos y fuente del servo.
- [ ] Cargar esta versión en la placa y registrar las salidas seriales.
- [ ] Verificar pulsos y límites mecánicos del servo.
- [ ] Ensayar arranque, 0 %, ≥70 % y conservación del estado entre 1–69 %.
- [ ] Comprobar recuperación de lecturas inválidas y cierre por ausencia de muestras.
- [ ] Medir la respuesta temporal del filtro y revisar el efecto de la saturación ADC.
- [ ] Repetir la caracterización con condiciones controladas y registrar datos.
- [ ] Completar el esquema eléctrico real y el enlace del video.

Una entrada que permanece en 4095 puede deberse a sequedad o a un problema eléctrico; la validez numérica no detecta por sí sola una desconexión del sensor.
