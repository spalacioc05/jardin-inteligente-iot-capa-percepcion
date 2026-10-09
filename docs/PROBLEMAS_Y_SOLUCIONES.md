# Problemas, soluciones y pendientes

| Situación | Qué se realizó | Qué queda pendiente |
|---|---|---|
| Dificultad para adquirir la bomba y retraso de componentes | Se utilizó un microservomotor para representar la activación del riego. | Adquirir la bomba e integrar el relé de 5 V. |
| HC-SR04 sin integración por adaptación de niveles de tensión, según el equipo | Se seleccionó el módulo para medir el nivel del tanque. | Verificar alimentación, adaptar ECHO y comprobar los niveles de TRIG del módulo. |
| Calibraciones diferentes entre ensayos | Se conservaron los valores visibles de cada captura. | Establecer un protocolo común con registros y condiciones de ensayo. |
| Placa y conexiones no identificables con certeza en las fotos | Se documentó una configuración de referencia separada del montaje real. | Confirmar serigrafía, GPIO y esquema eléctrico con el equipo. |
| Firmware de la demostración no disponible | Se desarrolló una implementación de referencia y se comprobó su lógica en PC. | Compilarla y validarla en la placa; contrastarla con el original si se recupera. |

Las acciones pendientes son propuestas de continuidad; aún no constituyen soluciones verificadas en hardware. Véase la [matriz de pruebas](PRUEBAS.md).