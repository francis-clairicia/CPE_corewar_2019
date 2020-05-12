# -*- coding: Utf-8

import os
import sys

IMG_FOLDER = os.path.join(sys.path[0], "img")
HELP_FOLDER = os.path.join(sys.path[0], "help")
EDITOR_SAVE_FILE = os.path.join(sys.path[0], "workspace.sav")

PROG_NAME_LENGTH = 128
COMMENT_LENGTH = 2048

T_REG = 1       # /* register */
T_DIR = 2       # /* direct  (ld  #1,r1  put 1 into r1) */
T_IND = 4       # /* indirect always relative */

REG_NUMBER = 16 # /* r1 <--> rx */

DIRECT_CHAR = '%'
LABEL_CHAR = ':'
SEPARATOR_CHAR = ','
LABEL_CHARS = "abcdefghijklmnopqrstuvwxyz_0123456789"

ARGS_TYPE = {
    "live": [T_DIR],
    "ld": [T_DIR | T_IND, T_REG],
    "st": [T_REG, T_IND | T_REG],
    "add": [T_REG, T_REG, T_REG],
    "sub": [T_REG, T_REG, T_REG],
    "and": [T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG],
    "or": [T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG],
    "xor": [T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG],
    "zjmp": [T_DIR],
    "ldi": [T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG],
    "sti": [T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG],
    "fork": [T_DIR],
    "aff": [T_REG]
}

MNEMONICS = tuple(ARGS_TYPE.keys())