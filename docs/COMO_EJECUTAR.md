# Puesta en marcha de la reconstrucción

> **Advertencia:** este firmware se redactó a partir de fotografías y descripciones. **No es el firmware original**, no se ha compilado en la instalación PlatformIO del equipo y no se ha ejecutado sobre su placa.

## Requisitos

- Visual Studio Code y extensión PlatformIO IDE.
- Toolchain ESP-IDF disponible por PlatformIO.
- ESP32 físico: confirmar si corresponde realmente a la variante DOIT ESP32 DEVKIT V1 sugerida por el nombre del entorno visible.
- Sonda resistiva de humedad + interfaz analógica; microservomotor; fuente adecuada para el servo.

## Pasos

1. Abrir la **raíz** del repositorio como proyecto PlatformIO.
2. Inspeccionar `platformio.ini`, `include/project_config.h` y las etiquetas impresas en la placa. Si la variante de ESP32 difiere, modificar la configuración.
3. Confirmar la **salida AO** del módulo de humedad; conectarla a un ADC compatible **solo después** de medir que la salida no supere los 3,3 V. Las imágenes no permiten certificar los pines usados.
4. Conectar la señal del servo al GPIO elegido **solo después** de identificar el pin real. Alimentar el servo de una fuente compatible y unir GND de la fuente con GND del ESP32. **No alimentarlo desde GPIO**.
5. Ajustar las lecturas `ADC_MOJADO`, `ADC_SECO` y los pulsos del servo a las condiciones reales.
6. Compilar y cargar con los controles habituales de PlatformIO o con `pio run -e esp32doit-devkit-v1 -t upload`.
7. Observar por consola con `pio device monitor -b 115200`.
8. Comprobar primero el control del servo sin acoplarlo a mecanismos ni a la bomba.

## Qué hace

- Tarea de muestreo con ADC1 y promedio móvil de 8 muestras (elección de esta reconstrucción).
- Tarea FreeRTOS de control mediante cola de longitud 1.
- Escala orientativa 0–100% entre `ADC_SECO` y `ADC_MOJADO`.
- Lectura 0%: orden de servo abierto. Lectura >=70%: servo cerrado. Valores intermedios: mantiene el estado previo (**decisión propuesta, no evidenciada**).
- Lectura inválida: servo cerrado (seguridad propuesta).

## Qué NO hace

No controla una bomba ni el relé de 5 V, no usa el HC-SR04, no lee un DHT11 y no implementa Wi-Fi, MQTTS, servidor ni dashboard. El repo documenta esos componentes solamente como futuros o no integrados.

## Comprobación de lógica en PC

```bash
make -C tests test
python3 scripts/verificar_evidencias.py
```

Estas verificaciones no sustituyen compilación ni pruebas en el ESP32. Los porcentajes de las fotos proceden de diferentes corridas de calibración y pueden diferir de la fórmula de referencia.
