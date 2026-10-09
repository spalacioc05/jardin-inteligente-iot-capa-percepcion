# Aspectos académicos por completar

La [matriz de requisitos](REQUISITOS_ENTREGA.md) recoge los nueve elementos formales. Los siguientes puntos requieren atención técnica para sustentar la entrega:

| Aspecto | Evidencia actual | Comprobación pendiente |
|---|---|---|
| Sensor analógico | Sonda resistiva y registros ADC. | Identificar el modelo y documentar la calibración del montaje definitivo. |
| Sensor digital | HC-SR04 seleccionado; DHT11 previsto en la propuesta. | Integrar y ensayar un sensor digital conforme al alcance exigido. |
| Actuación | Servo que representa el riego. | Mantener la distinción con una bomba real y documentar el circuito del servo. |
| Media móvil | Implementada y comprobada en PC en el código de referencia. | Verificar su respuesta temporal y efecto sobre el ruido en la placa. |
| FreeRTOS y ESP-IDF | Presentes en el código de referencia; PlatformIO visible en las capturas. | Compilar y ejecutar esta versión en el ESP32; no atribuirla al programa de la demostración sin confirmación. |
| Hardware y cableado | Fotografías del montaje. | Confirmar placa, GPIO, alimentación y adaptación de niveles. |

La entrega corresponde a un prototipo parcial de percepción. El repositorio ya es público; quedan por incorporar el enlace del video, los datos académicos pendientes y los resultados de las validaciones físicas.