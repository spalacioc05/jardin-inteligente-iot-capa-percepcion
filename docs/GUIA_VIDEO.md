# Guía para enlazar y presentar el video existente

Según lo informado por el equipo, **el video ya existe**; no se adjuntó aquí como archivo ni se proporcionó un enlace público. No se generó ni reemplazó ese video.

**Enlace de demostración:** `PENDIENTE_DE_URL_REAL` (reemplazar cuando el equipo lo suba).

## Secuencia de narración recomendada sobre el material real

1. Mostrar ESP32, sonda resistiva de dos electrodos y módulo de interfaz (fotos E02, E05, E14 y E15).
2. Explicar prueba de caracterización: lectura de 4095 en seco → 0 %, y cercanas a 2100 al humedecer → ≈100 %, según las capturas; valores variables entre corridas.
3. Mostrar montaje de servo y evidenciar con consola los mensajes `AUTO | servo ABIERTO` y `AUTO | servo CERRADO` (E16–E20).
4. Explicar que **el servo simula la apertura del riego**. No se empleó la bomba de agua ni se conectó el relé para controlar esa bomba.
5. Mostrar, si procede, el HC-SR04 y relé **como componentes seleccionados pero pendientes de integración**, no como circuito ya ensayado.
6. Cerrar con problemas reales, próximos pasos y limitaciones.

Evitar narrar que ya existe control por nivel del tanque, bomba activa, DHT11, MQTTS o dashboard. Quitar audio original y agregar narración humana solo si el equipo lo autoriza y verifica.
