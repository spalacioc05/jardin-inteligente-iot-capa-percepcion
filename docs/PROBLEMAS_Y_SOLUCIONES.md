# Problemas, soluciones y pendientes

> Distinguir **hechos reportados por integrantes** de posibles soluciones técnicas aún no ejecutadas.

| Situación | Estado de evidencia | Acción / resolución |
|---|---|---|
| Bomba de agua no disponible | **Reportado por el equipo** | Se usó un **microservo como simulador de riego**, no como una bomba real. |
| Retraso de componentes desde China | **Reportado por el equipo** | Se implementó un prototipo acotado para probar la lógica con piezas disponibles. |
| HC-SR04 sin integración por diferencias de voltaje | **Reportado por el equipo** | **Pendiente**: verificar alimentación, acondicionar ECHO a 3,3 V y comprobar TRIG; no afirmar que ya se resolvió. |
| Calibraciones diferentes entre ensayos | **Evidencia visible** | Separar capturas por sesión y etiquetar sus valores; falta protocolo único documentado. |
| Identificación exacta de pines y placa | **No recuperable desde fotografías** | Pendiente de foto de serigrafía y diagrama del equipo; no inventar pinout. |
| Uso del filtro de media móvil en firmware original | **No demostrado** | Esta reconstrucción **lo implementa**, pero debe compilarse y ensayarse para que sea resultado válido. |

**No atribuir** al equipo correcciones, mediciones o pruebas que no comunicó.
