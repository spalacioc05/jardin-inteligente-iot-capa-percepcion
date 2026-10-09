# Arquitectura: montaje observado vs. propuesta futura

## Montaje observado

```mermaid
flowchart LR
  subgraph F[Prototipo evidenciado]
    S["Sonda resistiva<br/>2 electrodos"] --> M["Interfaz de humedad<br/>AO / electrónica"]
    M --> E["ESP32<br/>GPIO exacto sin verificar"]
    E --> V["Microservo azul<br/>simulación de riego"]
    E --> C["Consola serial<br/>ADC · % · estados"]
  end
  classDef principal fill:#e3f2ed,stroke:#11694e,color:#124c3b
  classDef nota fill:#e9eef7,stroke:#45658a,color:#193858
  class S,M,E,V principal
  class C nota
```

Este diagrama es **de bloques y conexiones funcionales**, no el esquema eléctrico preciso que todavía exige la entrega. Las imágenes no permiten certificar los números de GPIO ni los voltajes de alimentación.

## Elementos fotografiados que NO deben dibujarse como conectados

```mermaid
flowchart LR
  R["Módulo relé 5 V
Fotografiado, pendiente"] -.-> B["Bomba DC
No disponible"]
  U["HC-SR04
Fotografiado"] -.-> T["Nivel del tanque
Pendiente"]
  D["DHT11
Propuesto, sin evidencia"]
  classDef pendiente fill:#fff4de,stroke:#bd7816,color:#663f07
  class R,B,U,T,D pendiente
```

## Pinout orientativo para el código reconstruido (NO certificado)

| Componente | Señal | Configuración de ejemplo | ¿Pudimos confirmar el pin real? |
|---|---|---|---|
| Módulo humedad | AO (analógica) | ADC1_CHANNEL_6 / GPIO34 **solo ESP32 clásico** | **No** |
| Módulo humedad | VCC, GND | Alimentación compatible, GND común | **No** |
| Microservo | Control PWM | GPIO18 **ejemplo** | **No** |
| Microservo | Alimentación, GND | Fuente externa compatible, tierra común | **No** |
| Relé de 5 V | Control | **No configurado** | No conectado según evidencia |
| HC-SR04 | TRIG / ECHO | **No configurados** | No integrado según mensaje |

### Seguridad eléctrica

- El GPIO de ESP32 no es una fuente de potencia para un servo o una bomba.
- La entrada analógica del ESP32 **no tolera automáticamente 5 V**; verificar la tensión en AO con multímetro.
- El HC-SR04 suele alimentarse a 5 V y su pin ECHO puede entregar 5 V. Antes de conectarlo al ESP32, diseñar un **divisor resistivo o adaptación de nivel** para ECHO, con especificaciones del módulo exacto. No se asume que el TRIG requiera amplificador sin comprobar su hoja de datos y comportamiento.
- El relé requiere verificar tensión de la bobina/módulo, alimentación, activación lógica y aislamiento. Nunca alimentar la bomba desde pines del ESP32.
- El sensor resistivo de humedad montado NO es lo mismo que el capacitivo de la propuesta.

## Lógica demostrada por mensajes del equipo

```mermaid
stateDiagram-v2
  [*] --> Sin_confirmar: inicialización
  Sin_confirmar --> Abierto: humedad == 0 %
  Sin_confirmar --> Cerrado: humedad >= 70 %
  Abierto --> Cerrado: humedad >= 70 %
  Cerrado --> Abierto: humedad == 0 %
  note right of Abierto: Servo abierto
Bomba simulada activa
  note right of Cerrado: Servo cerrado
Bomba simulada apagada
```

Los casos `1–69 %` **no se describen con certeza en las evidencias**. En la implementación reconstruida se retiene el estado anterior por decisión de diseño, nunca como afirmación sobre el firmware original.

## Proyecto global (NO implementado en esta fase)

```mermaid
flowchart LR
  S["Percepción: ESP32 + sensores + actuador"] --> N["Red: Wi-Fi + MQTT/TLS"]
  N --> A["Aplicación: broker, BD y dashboard en Raspberry Pi"]
  A -. comandos .-> N
  N -. control remoto .-> S
  classDef presente fill:#d9f4e7,stroke:#187651,color:#155237
  classDef futuro fill:#e7e9ed,stroke:#6b7280,color:#303845
  class S presente
  class N,A futuro
```

Futuro: cableado real definitivo, HC-SR04 adaptado, medición de nivel de tanque, protección por vacío, relé y bomba, nuevas pruebas y desarrollo de capas red/aplicación.
