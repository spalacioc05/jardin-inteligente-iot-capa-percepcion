# Estado del proyecto

Esta primera entrega reúne la caracterización de humedad y un prototipo con servo, documentados mediante [20 fotografías](EVIDENCIAS.md) y las descripciones del equipo.

## Resultados disponibles

- Sonda resistiva de dos electrodos, módulo de interfaz y ESP32 utilizados para obtener lecturas analógicas.
- Ensayos con agua y papel absorbente, con registros secos de ADC 4095 y lecturas húmedas e intermedias bajo diferentes calibraciones.
- Conversión de las lecturas a una escala porcentual mostrada en consola.
- Servomotor utilizado para representar el riego. El equipo reporta apertura a 0 % y cierre a partir de 70 %; E18 muestra estados abierto y cerrado.

## Diferencias con la propuesta inicial

| Propuesta | Estado de esta entrega |
|---|---|
| Sensor capacitivo de humedad | Se utilizó una sonda resistiva. |
| Sensor de nivel analógico del kit | Se seleccionó un HC-SR04, aún sin integración funcional. |
| Bomba DC controlada por relé de 5 V | El servo representa el riego; el relé está fotografiado y la bomba pendiente de adquisición. |
| DHT11 | Sin evidencia de integración. |
| Riego según perfil de planta y disponibilidad de agua | Objetivo del proyecto; aún no hay perfiles configurables ni control por nivel del tanque. |
| MQTT/TLS, Raspberry Pi y dashboard | Corresponden a etapas posteriores. |

## Alcance del firmware publicado

El código de [src/](../src/) es una implementación de referencia reconstruida a partir del comportamiento conocido, con PlatformIO, ESP-IDF y FreeRTOS. No se ha confirmado que sea idéntico al programa utilizado en la demostración física.

Los GPIO, pulsos del servo y puntos de calibración son parámetros de referencia. El promedio móvil, el arranque en cerrado, el tratamiento de errores y la conservación del estado entre 1–69 % son decisiones del código publicado, sin evidencia suficiente para atribuirlas al firmware original. El monitor muestra PlatformIO, pero las imágenes por sí solas no permiten verificar el framework ni la organización de tareas del programa original.

Las [pruebas en PC](PRUEBAS.md) verifican la lógica de referencia. La compilación con PlatformIO y la validación en la placa siguen pendientes, junto con la identificación exacta del hardware, el esquema eléctrico y el enlace del video.