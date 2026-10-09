"""Comprueba inventario, archivos PNG y referencias del catálogo, sin hardware."""
from pathlib import Path
import csv

root = Path(__file__).resolve().parents[1]
csvpath = root / "assets" / "inventario.csv"
with csvpath.open(encoding="utf-8", newline="") as f:
    items = list(csv.DictReader(f))


def require(condition, message):
    if not condition:
        raise SystemExit(message)


require(len(items) == 20, f"Se esperaban 20 evidencias, hay {len(items)}")
require({item["id"] for item in items} == {f"E{i:02}" for i in range(1, 21)},
        "Los identificadores deben ser E01 a E20, sin duplicados")
paths = {item["ruta"] for item in items}
require(len(paths) == 20, "Hay rutas duplicadas en el inventario")
photos = {p.relative_to(root).as_posix() for p in (root / "assets/fotos").iterdir()
          if p.is_file()}
require(paths == photos, "El inventario y assets/fotos no contienen los mismos archivos")
catalog = (root / "docs/EVIDENCIAS.md").read_text(encoding="utf-8")
for item in items:
    p = root / item["ruta"]
    require(p.is_file(), f"Foto no encontrada: {p}")
    with p.open("rb") as f:
        require(f.read(8) == b"\x89PNG\r\n\x1a\n", f"Firma PNG inválida: {p}")
    require(f"(../{item['ruta']})" in catalog, f"Falta imagen en el catálogo: {p.name}")
    require(item["origen"] in catalog, f"Falta origen en el catálogo: {item['id']}")
print("OK: 20 fotografías PNG, inventario único y referencias del catálogo")
