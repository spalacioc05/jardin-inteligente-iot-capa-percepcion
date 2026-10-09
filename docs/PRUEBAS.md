# Matriz de pruebas y evidencias

## Evidencias de la experiencia del equipo

| ID | Prueba / observación | Fuente | Estado |
|---|---|---|---|
| P-01 | Valor de ADC seco ≈4095 (0 %) | E01, E06 | **Observado en captura** |
| P-02 | Valores húmedos ≈2064–2100 (100 %) | E03, E09 | **Observado en captura** |
| P-03 | Cambios porcentuales durante acondicionamiento | E09, E11 | **Observado en captura** |
| P-04 | Servo ABIERTO y CERRADO según mensajes seriales | E18, E19, E20 y texto del equipo | **Demostración parcial** |
| P-05 | Control de bomba física por relé | E12 (foto de componente) | **No implementado/evidenciado** |
| P-06 | Lectura nivel HC-SR04 | E13 (componente aislado) | **No implementado/evidenciado** |
| P-07 | Lectura del DHT11 | Sin evidencia | **No implementado/evidenciado** |
| P-08 | Comunicación Wi-Fi/MQTTS | Sin evidencia | **No implementado/evidenciado** |
| P-09 | FreeRTOS y ESP-IDF usados por firmware ORIGINAL | Solo PlatformIO en consola | **No verificable sin código original** |

## Pruebas automáticas de la reconstrucción

Las pruebas nativas de `tests/test_control_logic.c` comprueban conversión de ADC a porcentaje, extremos, salidas del control, lectura inválida y media móvil. Ejecutarlas con `make -C tests test`. Estas verifican lógica **en PC**, no temporización de ESP32, sensores reales ni comportamiento mecánico del servo.

## Pendientes de validación física

- [ ] Verificar placa ESP32 y pinout real.
- [ ] Confirmar niveles eléctricos y fuente del servo.
- [ ] Compilar el firmware de este repo con PlatformIO + ESP-IDF.
- [ ] Cargarlo sobre la placa y verificar salidas seriales.
- [ ] Medir límites mecánicos correctos del servo y evitar topes.
- [ ] Confirmar respuesta a 0 %, ≥70 % y 1–69 %.
- [ ] Verificar estabilidad con suelo y material experimental reproducible.
- [ ] Documentar esquema físico real con GPIO, conectores y alimentación.
