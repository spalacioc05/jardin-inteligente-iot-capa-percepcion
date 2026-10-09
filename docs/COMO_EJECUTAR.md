# Puesta en marcha del firmware de referencia

Esta implementación se reconstruyó a partir del comportamiento conocido. La compilación con PlatformIO y la ejecución sobre la placa del equipo están pendientes.

## Preparar el entorno

Instalar PlatformIO Core o la extensión PlatformIO IDE para Visual Studio Code y abrir la raíz del repositorio. El entorno `esp32doit-devkit-v1` utiliza ESP-IDF; la [plataforma Espressif32 6.13.0](https://github.com/platformio/platform-espressif32/releases/tag/v6.13.0) está fijada para mantener la misma versión de referencia.

Compilar sin conectar la placa:

```bash
pio run -e esp32doit-devkit-v1
```

## Revisar el montaje antes de cargar

1. Confirmar la referencia de la placa y contrastarla con [platformio.ini](../platformio.ini).
2. Revisar [project_config.h](../include/project_config.h). ADC1, canal 6 (GPIO34 en ESP32 clásico) y GPIO18 son **ejemplos**, no pines recuperados del montaje.
3. Medir la salida AO y confirmar que sea compatible con la entrada ADC. Verificar la alimentación de la interfaz y la tierra común.
4. Confirmar la señal y la fuente del servo; no alimentarlo desde un GPIO. Documentar el cableado real según la [arquitectura](ARQUITECTURA.md).
5. Ajustar `ADC_MOJADO`, `ADC_SECO` y los pulsos de apertura/cierre al ensayo y al recorrido mecánico, evitando topes.

Una vez revisados estos puntos, cargar y abrir el monitor:

```bash
pio run -e esp32doit-devkit-v1 -t upload
pio device monitor -b 115200
```

Si hay varios dispositivos, seleccionar el puerto correspondiente con las opciones de PlatformIO. Ensayar primero el servo sin acoplarlo a mecanismos.

## Comportamiento esperado de esta versión

- Muestreo ADC de 12 bits cada 1000 ms y media móvil de ocho muestras.
- Conversión relativa a 0–100 %, redondeada al entero más cercano.
- Servo inicialmente cerrado; apertura a 0 % y cierre desde 70 %.
- Entre 1–69 %, conservación del estado anterior.
- Lectura inválida: cierre y reinicio del filtro; ausencia de muestras durante 3000 ms: cierre.
- Cola de una lectura entre adquisición y control; mensajes de estado por consola.

El filtro introduce retardo ante cambios de humedad: la ventana completa cubre ocho muestras. Una lectura ADC válida de 4095 se interpreta como el extremo seco; **no permite distinguir por sí sola sequedad, saturación o una desconexión eléctrica**. La respuesta al fallo de sensor debe ensayarse en hardware.

## Pruebas en PC

Con Make, GCC (o compilador C equivalente) y Python 3:

```bash
make -C tests test
python scripts/verificar_evidencias.py
```

En Windows con MinGW/MSYS2, agregar su directorio de herramientas al `PATH` y utilizar:

```powershell
mingw32-make -C tests test CC=gcc
python scripts/verificar_evidencias.py
```

La [matriz de pruebas](PRUEBAS.md) separa estas verificaciones de los ensayos físicos.