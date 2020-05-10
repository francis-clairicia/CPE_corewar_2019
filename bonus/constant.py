# -*- coding: Utf-8

import os
import sys

RESSOURCES_FOLDER = os.path.join(sys.path[0], "ressources")
IMG_FOLDER = os.path.join(RESSOURCES_FOLDER, "img")
if not os.path.isdir(RESSOURCES_FOLDER):
    raise FileNotFoundError("Ressources folder not present")
if not os.path.isdir(IMG_FOLDER):
    raise FileNotFoundError("Image folder not present")
IMG = {
    "logo": os.path.join(IMG_FOLDER, "logo_menu.png"),
    "menu_bg": os.path.join(IMG_FOLDER, "menu_background.png")
}
for img in IMG.values():
    if not os.path.isfile(img):
        raise FileNotFoundError(f"{img} not found")