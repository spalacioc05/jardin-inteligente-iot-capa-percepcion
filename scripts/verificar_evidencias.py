"""Verifica integridad básica de las 20 imágenes entregadas por el equipo.
No valida montaje ni firmware en ESP32.
"""
from pathlib import Path
import csv
root = Path(__file__).resolve().parents[1]
csvpath = root / "assets" / "inventario.csv"
with csvpath.open(encoding="utf-8", newline="") as f:
    items = list(csv.DictReader(f))
assert len(items) == 20, f"Se esperaban 20 evidencias, hay {len(items)}"
for item in items:
    p = root / item["ruta"]
    assert p.is_file() and p.stat().st_size > 0, f"Foto no encontrada: {p}"
print("OK: 20 fotografías originales identificadas en inventario (integridad básica)")
