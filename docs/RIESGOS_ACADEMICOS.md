# Riesgos académicos y cómo comunicarlos con transparencia

Este documento no modifica el montaje ya realizado; alerta de las posibles diferencias entre la experiencia disponible y los requisitos del curso.

| Exigencia | Evidencia compartida | Riesgo / acción honesta |
|---|---|---|
| Sensor analógico | **Sí:** sonda resistiva y registros ADC. | Documentar modelo real y esquema eléctrico. |
| Sensor digital en arquitectura general | **No demostrado:** HC-SR04 solo fotografiado; DHT11 solo previsto. | Señalar alcance parcial. Solo marcar «integrado» cuando exista prueba física. |
| Actuador | **Sí:** servo como simulador. | No denominarlo bomba de agua ni atribuir al relé una conmutación inexistente. |
| Filtro media móvil | **No verificable** en firmware original; **sí redactado** en código reconstruido. | No declarar funcionamiento real sin flashear y medir. |
| FreeRTOS + PlatformIO / ESP-IDF | PlatformIO aparece en consola. Código original no adjunto. | Proyecto nuevo usa las herramientas requeridas, **sin validación de placa**. Es importante probarlo antes del informe. |
| Referencia exacta y pinout | Foto ESP32 visible, texto de entorno `esp32doit-devkit-v1`. | Confirmar etiqueta exacta, GPIO, voltajes y alimentación. No inferir conexión solo por colores. |
| Fotos de montaje | **Sí:** 20 archivos proporcionados. | Elegir fotos E05, E14, E15, E16, E17, E19, E20. |
| Video | Usuario reporta video disponible pero **no adjuntó archivo ni URL**. | Agregar enlace real y narración veraz. |
| Repositorio público | Se genera ZIP para publicación posterior. | No afirmar que el GitHub fue creado hasta compartir URL confirmada. |
| Problemas-soluciones y uso de IA | Documentado con distinciones reportado / propuesto. | Revisar y firmar con el equipo. |

**Recomendación de presentación:** defender esta entrega como un **prototipo parcial de percepción** y explicar explícitamente qué funcionalidades quedaron para las siguientes iteraciones. Es mejor reflejar con precisión los resultados disponibles que afirmar conexiones o integraciones que no existen.
