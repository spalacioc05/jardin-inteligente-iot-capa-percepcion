# Publicar el ZIP como repositorio público en GitHub

**Nombre recomendado (slug):** `jardin-inteligente-iot-capa-percepcion`.

El asistente no pudo crear directamente el repositorio porque la conexión disponible permite manipular repositorios existentes, pero no expone una acción para **crear uno nuevo**. Por eso se entrega este paquete completo para subirlo a tu cuenta. **Nada se ha publicado en GitHub.**

## Por la página web

1. Abrir https://github.com/new, seleccionar la cuenta correcta y crear el repositorio con el nombre indicado y visibilidad **Public**.
2. Para subida simple, descomprimir este ZIP localmente.
3. En el repo vacío, elegir `uploading an existing file`; cargar la estructura respetando directorios. Es preferible utilizar Git local para cargar muchos archivos y carpetas.
4. Revisar que `README.md` se visualice, que `assets/fotos/` contenga las 20 imágenes y que GitHub Actions solo anuncie **pruebas host**.
5. Añadir el enlace real al video y los correos institucionales que el equipo autorice a publicar.

## Por Git en una terminal (recomendado)

```bash
# Descomprime el ZIP y abre una terminal DENTRO de la carpeta raíz
cd jardin-inteligente-iot-capa-percepcion
git init -b main
git add .
git commit -m "docs: primera entrega de percepcion IoT (evidencias y firmware reconstruido)"
git remote add origin https://github.com/TU_USUARIO/jardin-inteligente-iot-capa-percepcion.git
git push -u origin main
```

**Importante:** crea antes un repo vacío en GitHub; sustituye `TU_USUARIO` por tu usuario auténtico. Evita inicializar el repo remoto con otro README si ya subes este.

## Revisión previa de privacidad y autoría

El repositorio será **público**. Los tres integrantes deberían revisar que las fotos pueden publicarse, que no muestran secretos o datos privados, y que están de acuerdo con publicar nombres y cualquier correo institucional. El material docente ZIP y PDFs completos no se redistribuyen aquí: se documentan sus referencias.

## Actualizaciones posteriores

Cuando dispongan del `.c` original empleado en el montaje, **no lo sustituyan silenciosamente por esta reconstrucción**: guarden el original, citen su procedencia y comparen/actualicen `ESTADO_REAL.md` y las pruebas. Si validan esta reconstrucción sobre placa, anexen el log de compilación y evidencias nuevas con su fecha.
