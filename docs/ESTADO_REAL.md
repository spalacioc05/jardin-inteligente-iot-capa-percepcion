# Estado real del trabajo y límites de la evidencia

> Esta página prevalece sobre cualquier esquema de arquitectura futura. Solo describe lo que se ve en las 20 imágenes y lo que el equipo indicó expresamente en sus mensajes del **7 de octubre de 2026**. No hemos recibido el código fuente original ni un registro de pruebas de compilación.

## Confirmado con fotografías o mensajes del equipo

1. Se realizó **caracterización de una sonda resistiva de humedad de dos electrodos** conectada a un módulo de interfaz y un ESP32.
2. En una prueba seca, el monitor serie indica **ADC 4095 → humedad 0 %**.
3. En pruebas húmedas se observan lecturas **aprox. 2064–2100 → humedad 100 %** con la calibración particular de cada corrida. Otras capturas muestran valores intermedios.
4. Se realizó un **prototipo con servomotor** para representar el estado de riego: **servo abierto = bomba funcionando (simulada)** y **servo cerrado = bomba apagada (simulada)**.
5. El equipo describió: **0 % de humedad → servo abierto** y **humedad ≥70 % → servo cerrado**. Capturas del monitor muestran estados `AUTO | servo ABIERTO/CERRADO`.
6. El equipo dispone o seleccionó un **módulo de relé de 5 V**, que **no se ve conectado como parte del prototipo funcional**.
7. El equipo seleccionó un **HC-SR04 para el nivel del tanque**, **sin integración funcional**, según sus mensajes por asuntos de niveles de tensión.
8. **No se consiguió la bomba de agua** para esta entrega, según los mensajes del equipo; se esperan componentes demorados del envío.

## Diferencias con la propuesta inicial

| Propuesta inicial | Evidencia real de esta entrega |
|---|---|
| Sensor **capacitivo** de humedad del suelo | Sonda **resistiva** de dos electrodos y módulo de interfaz |
| Sensor de nivel **analógico** del kit | HC-SR04 **seleccionado**, pero **no integrado** |
| Bomba DC mediante relé de 5 V | **Servo demostrativo**; bomba ausente; relé fotografiado |
| DHT11 de temperatura y humedad ambiental | **Sin evidencia** de integración en las fotos compartidas |
| Control del nivel mínimo de tanque | **No implementado en el prototipo evidenciado** |
| MQTT/TLS, Raspberry Pi y dashboard | **No implementados en la evidencia**; capas posteriores |

## Lo que las imágenes NO prueban

- No muestran de forma inequívoca referencia comercial exacta de placa ESP32, módulo resistivo o servo.
- No permiten identificar con certeza número de GPIO, fuente de alimentación, resistencias o recorrido mecánico del servo.
- No prueban que la bomba o el relé estén actuando sobre agua.
- No prueban sensor ultrasónico conectado, DHT11, filtrado de media móvil, conectividad o telemetría en JSON.
- No permiten asegurar qué ocurrió **entre 1 % y 69 % de humedad** ni el firmware exacto empleado.
- No demuestran que se haya utilizado FreeRTOS con ESP-IDF en el firmware original: aparece PlatformIO y un identificador de placa, pero **el código original no fue adjuntado**.

## Qué es el código de este repositorio

El código en `src/` es una **implementación didáctica reconstruida** que sigue el comportamiento declarado y emplea explícitamente FreeRTOS, PlatformIO y ESP-IDF, tal como exige la consigna del profesor. Sus pines y configuraciones son **supuestos configurables** y **no equivalen a las conexiones físicas verificadas**. Los controles de seguridad y el tratamiento de estados intermedios son **decisiones de implementación nuevas, no hechos probados sobre el programa original**.

> **No describir el firmware reconstruido como el archivo `.c` escrito o cargado por Mariana u otro integrante el día del video.**
