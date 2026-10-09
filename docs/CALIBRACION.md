# Caracterización del sensor de humedad

## Registros de los ensayos

| Imagen | Escenario | ADC que aparece | Humedad que aparece | Nota |
|---|---|---|---|---|
| [E01](EVIDENCIAS.md#e01) | Seco | 4095 | 0 % | Primer registro mostrado; min/max de esa corrida |
| [E03](EVIDENCIAS.md#e03) | Húmedo | 2077, 2068, 2075, 2079, 2072 | 100 % | MIN 2064, MAX 4095 |
| [E06](EVIDENCIAS.md#e06) | Seco | 4095 | 0 % | MIN aprox. 2683: corrida diferente |
| [E09](EVIDENCIAS.md#e09) | Húmedo/se va secando | 2100, 2179, 2202, 2244, 2315 | 100, 98, 97, 95, 91 % | Registro de transición |
| [E11](EVIDENCIAS.md#e11) | Estado intermedio | 2671, 2545, 2468, 2462, 2449 | 73, 79, 83, 83, 84 % | Valores visuales redondeados |
| [E18](EVIDENCIAS.md#e18) | Prototipo con servo | ~1655–1686 húmedo, 4095 seco | 100 % y 0 % | Calibración aparentemente distinta |

El mismo valor ADC puede convertirse a distinto porcentaje si cambian los puntos de calibración. Las capturas muestran diferentes mínimos entre sesiones y no permiten reconstruir todo el procesamiento original.

## Conversión del firmware de referencia

```text
humedad_pct = limitar[0,100](100 * (ADC_seco - ADC_actual) / (ADC_seco - ADC_mojado))
```

- `ADC_seco = 4095` y `ADC_mojado = 2100` son **valores de ejemplo tomados de una de las corridas**, no definitivos para toda planta, sustrato o hardware.
- En el código de referencia se convierte la media móvil y se redondea al entero más cercano. Por ejemplo, ADC 2671 se convierte en 71 %, mientras E11 muestra 73 %. No se conoce el procesamiento completo del programa original, por lo que no se ajusta la fórmula para forzar coincidencias.
- Las fotos emplean agua y papel absorbente; **no constituyen calibración agronómica precisa de contenido volumétrico del suelo**.
- Una sonda resistiva expuesta permanentemente a corriente puede corroerse. Evaluar después un sensor capacitivo o energización limitada de la sonda.

## Procedimiento reproducible a realizar con el equipo

1. Identificar la salida **AO** del módulo y medir el voltaje antes de conectarla al ADC del ESP32.
2. Registrar repetidamente el ADC con la sonda seca.
3. Registrar con la sonda en un medio húmedo de ensayo controlado y anotar la condición exacta.
4. Calcular los puntos de calibración y anotar fecha, método, temperatura y montaje.
5. Confirmar que no se invierte el signo de la escala y evaluar ruido, tolerancia y saturación.
6. Tomar nuevas fotografías y datos si se ejecutan ensayos posteriores, separándolos de los actuales.
