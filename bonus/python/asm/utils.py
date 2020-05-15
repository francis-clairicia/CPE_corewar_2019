# -*- coding: Utf-8 -*

import os

def get_filename(path: str):
    head, tail = os.path.split(path)
    return tail or os.path.basename(head)

def remove_color_characters(string: str):
    index = string.find("\033")
    while index != -1:
        end = string[index:].find("m")
        string = string[:index] + string[index + end + 1:]
        index = string.find("\033")
    return string