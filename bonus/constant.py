# -*- coding: Utf-8

import os
import sys

RESSOURCES_FOLDER = os.path.join(sys.path[0], "ressources")
IMG_FOLDER = os.path.join(RESSOURCES_FOLDER, "img")
FONT_FOLDER = os.path.join(RESSOURCES_FOLDER, "font")
if not os.path.isdir(RESSOURCES_FOLDER):
    raise FileNotFoundError("Ressources folder not present")
if not os.path.isdir(IMG_FOLDER):
    raise FileNotFoundError("Image folder not present")
if not os.path.isdir(FONT_FOLDER):
    raise FileNotFoundError("Font folder not present")
IMG = {
    "logo": os.path.join(IMG_FOLDER, "logo_menu.png"),
    "menu_bg": os.path.join(IMG_FOLDER, "menu_background.png")
}
FONT = {
    "death_star": os.path.join(FONT_FOLDER, "death_star.otf")
}
for dictionnary in [IMG, FONT]:
    for path in dictionnary.values():
        if not os.path.isfile(path):
            raise FileNotFoundError(f"{path} not found")