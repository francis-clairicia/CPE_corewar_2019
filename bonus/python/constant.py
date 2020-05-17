# -*- coding: Utf-8

import os
import sys

def set_constant_directory(*path, special_msg=None) -> str:
    all_path = os.path.join(*path)
    if not os.path.isdir(all_path):
        if special_msg is not None:
            raise FileNotFoundError(special_msg)
        raise FileNotFoundError(f"{all_path} folder not found")
    return all_path

def set_constant_file(*path, special_msg=None) -> str:
    all_path = os.path.join(*path)
    if not os.path.isfile(all_path):
        if special_msg is not None:
            raise FileNotFoundError(special_msg)
        raise FileNotFoundError(f"{all_path} not found")
    return all_path

RESSOURCES_FOLDER = set_constant_directory(sys.path[0], "ressources", special_msg="Ressources folder not present")
IMG_FOLDER = set_constant_directory(RESSOURCES_FOLDER, "img", special_msg="Image folder not present")
FONT_FOLDER = set_constant_directory(RESSOURCES_FOLDER, "font", special_msg="Font folder not present")
AUDIO_FOLDER = set_constant_directory(RESSOURCES_FOLDER, "audio", special_msg="Audio folder not present")
CHAMPIONS_FOLDER = set_constant_directory(os.path.split(sys.path[0])[0], "champions", special_msg="Champions folder not present")
IMG = {
    "logo": set_constant_file(IMG_FOLDER, "logo_menu.png"),
    "menu_bg": set_constant_file(IMG_FOLDER, "menu_background.png"),
    "build": set_constant_file(IMG_FOLDER, "build_512px.png"),
    "valide": set_constant_file(IMG_FOLDER, "valide.png"),
}
FONT = {
    "death_star": set_constant_file(FONT_FOLDER, "death_star.otf")
}
AUDIO = {
    "ancient_game_open": set_constant_file(AUDIO_FOLDER, "ancient_game_open.ogg"),
    "clank": set_constant_file(AUDIO_FOLDER, "clank.ogg"),
    "laser": set_constant_file(AUDIO_FOLDER, "laser.ogg"),
    "dark_techno_city": set_constant_file(AUDIO_FOLDER, "dark_techno_city.ogg"),
    "crusaders": set_constant_file(AUDIO_FOLDER, "crusaders_approaching.ogg"),
    "battle": set_constant_file(AUDIO_FOLDER, "battle_of_the_ancients.ogg"),
    "ready": set_constant_file(AUDIO_FOLDER, "ready.ogg"),
    "finish": set_constant_file(AUDIO_FOLDER, "finish_him.ogg"),
}
ASM = set_constant_file(sys.path[0], "asm", "asm_compiler", special_msg="'asm_compiler' binary not here")
EDITOR = set_constant_file(sys.path[0], "asm", "asm.py", special_msg="Editor not here")
COREWAR = set_constant_file(sys.path[0], "corewar", special_msg="'corewar' binary not here")

MAX_NB_PLAYERS = 4