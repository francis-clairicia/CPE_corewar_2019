# -*- coding: Utf-8 -*

import os

def get_champion_value(filepath: str, instruction: str) -> (str, None):
    if not os.path.isfile(filepath):
        return None
    with open(filepath, "r") as file:
        content = file.read().splitlines()
    for line in content:
        idx = line.find(instruction)
        if idx >= 0:
            line = line[idx:]
            first_quote = line.find('"')
            if first_quote == -1:
                break
            second_quote = line.find('"', first_quote + 1)
            if second_quote == -1:
                break
            return line[first_quote + 1:second_quote]
    return None

def get_champion_name(filepath: str) -> str:
    name = get_champion_value(filepath, ".name")
    if name is None:
        return "Unnamed"
    return name

def get_champion_comment(filepath: str) -> str:
    name = get_champion_value(filepath, ".comment")
    if name is None:
        return "No comments"
    return name