# Arquitectura de percepción

## Montaje demostrado

```mermaid
flowchart LR
  S["Sonda resistiva<br/>Dos electrodos"] --> I["Interfaz de humedad<br/>Salida analógica AO"]
  I --> E["ESP32<br/>Lectura ADC"]
  E --> V["Microservomotor<br/>Riego simulado"]
  E --> C["Monitor serial<br/>ADC · humedad · estado"]
  classDef sensor fill:#eaf8f1,stroke:#187651,color:#12543a
  classDef control fill:#e4f1ff,stroke:#3168a8,color:#174471
  class S,I,V sensor
  class E,C control
```

[Fuente Mermaid](../assets/diagramas/arquitectura-actual.mmd). Las flechas representan relaciones funcionales, no un esquema eléctrico. Las fotografías no permiten confirmar los GPIO ni la alimentación de cada componente.

## Conexiones de referencia

Estos valores corresponden a [project_config.h](../include/project_config.h); deben contrastarse con el montaje antes de cargar el firmware.

| Componente | Señal | Configuración de referencia | Confirmación física |
|---|---|---|---|
| Interfaz de humedad | AO | ADC1, canal 6 / GPIO34, solo ESP32 clásico | Pendiente |
| Interfaz de humedad | VCC y GND | Alimentación compatible con la salida analógica y tierra común | Pendiente |
| Microservomotor | PWM | GPIO18, 50 Hz; pulsos de 1000 y 2000 µs | Pendiente de pin y recorrido |
| Microservomotor | Alimentación y GND | Fuente adecuada para el servo y tierra común con ESP32 | Pendiente |
| Relé de 5 V | Control | Sin GPIO configurado | Sin integrar |
| HC-SR04 | TRIG y ECHO | Sin GPIO configurados | Sin integrar |

La entrada ADC del ESP32 debe recibir una tensión compatible con sus especificaciones; la atenuación no la hace tolerante a 5 V. Medir AO antes de conectarla. El servo requiere una fuente adecuada: un GPIO entrega la señal de control, no su potencia.

Para una futura integración del HC-SR04 se debe comprobar la tensión de ECHO y adaptar el nivel al ESP32 cuando corresponda. También deben verificarse la alimentación y los niveles de control del módulo relé. Estos trabajos siguen pendientes; no se dispone de un esquema eléctrico definitivo.

## Firmware de referencia

```mermaid
flowchart TD
  A["Tarea de adquisición<br/>ADC1 · cada 1000 ms"] --> B{"¿Lectura válida?"}
  B -->|Sí| F["Media móvil de 8 muestras<br/>Conversión a 0–100 %"]
  B -->|No| I["Reiniciar filtro<br/>Marcar lectura inválida"]
  F --> Q["Cola de una lectura<br/>Conserva la más reciente"]
  I --> Q
  Q --> C["Tarea de control<br/>Umbrales y estado anterior"]
  C --> P["LEDC · 50 Hz<br/>Orden al servo"]
  T["Sin muestras durante 3000 ms"] -.-> C
  classDef proceso fill:#eaf8f1,stroke:#187651,color:#12543a
  classDef control fill:#e4f1ff,stroke:#3168a8,color:#174471
  class A,B,F,I proceso
  class Q,C,P,T control
```

El filtro utiliza únicamente las muestras disponibles durante el arranque, sin completar la ventana con ceros. Tras un error de adquisición, comienza una ventana nueva. La cola evita acumular lecturas antiguas; un error de lectura o tres segundos sin muestras produce una orden de cierre.

El PWM inicia en cerrado. Si no se puede crear la cola o alguna tarea, se registra el error y se liberan los recursos creados para la adquisición y el control. Los errores de inicialización ADC/PWM se gestionan mediante `ESP_ERROR_CHECK`. Estas medidas no sustituyen una protección física ni garantizan el cierre ante pérdida de alimentación.

## Estados del control de referencia

```mermaid
stateDiagram-v2
  [*] --> Cerrado: inicio
  Cerrado --> Abierto: humedad = 0 %
  Abierto --> Cerrado: humedad >= 70 %
  Abierto --> Cerrado: lectura inválida o sin muestras
  Cerrado --> Cerrado: humedad entre 1 y 69 %
  Abierto --> Abierto: humedad entre 1 y 69 %
  note right of Cerrado
    Riego simulado desactivado
  end note
  note right of Abierto
    Riego simulado activo
  end note
```

[Fuente Mermaid](../assets/diagramas/estados-control.mmd). Los umbrales de 0 % y ≥70 % provienen del comportamiento reportado. El estado inicial, la conservación del estado entre 1–69 % y las respuestas a errores son decisiones de esta implementación, sin confirmación en el firmware de la demostración.

## Continuación del proyecto

El relé y el HC-SR04 están fotografiados, pero no forman parte de la cadena funcional anterior. La propuesta también contempla DHT11 y capas de red y aplicación, sin integración demostrada en esta entrega.

```mermaid
flowchart TB
  A["Prototipo actual<br/>Sensor resistivo · ESP32 · servo"] --> B["Pendiente<br/>Confirmar placa, GPIO y alimentación"]
  B --> C["Pendiente<br/>Integrar HC-SR04 y medir nivel del tanque"]
  C --> D["Pendiente<br/>Adquirir bomba e integrar relé"]
  D --> E["Capas posteriores<br/>Wi-Fi · MQTT/TLS"]
  E --> F["Aplicación futura<br/>Raspberry Pi · base de datos · dashboard"]
  classDef actual fill:#eaf8f1,stroke:#187651,color:#12543a
  classDef futuro fill:#f1f3f5,stroke:#64748b,color:#334155
  class A actual
  class B,C,D,E,F futuro
```

[Fuente Mermaid](../assets/diagramas/evolucion.mmd). Aquí las flechas indican etapas de desarrollo, no conexiones eléctricas.