# -*- coding: Utf-8 -*

import os
import re
import subprocess
from typing import List, Tuple
import pygame
from constant import FONT, AUDIO, ASM, COREWAR
from my_pygame import Window, Text, RectangleShape
from my_pygame.colors import YELLOW, TRANSPARENT, BLUE_LIGHT, BLUE_DARK, CYAN, GREEN, MAGENTA
from loading import Loading
from asm.constants import MEMSIZE
from asm.utils import remove_color_characters

HIGHLIGHT_COLOR = {
    36: CYAN,
    32: GREEN,
    35: MAGENTA,
    33: YELLOW
}

PLAYER_COLOR = [
    36,
    32,
    35,
    33
]

class Animation(Text):
    def __init__(self, master):
        Text.__init__(self, str(), (FONT["death_star"], 200), YELLOW, center=master.center)
        self.ready_sound = pygame.mixer.Sound(AUDIO["ready"])
        self.finish_sound = pygame.mixer.Sound(AUDIO["finish"])
        self.master = master
        self.winner = None

    def start(self):
        self.ready_sound.play()
        self.master.after(650, self.show_ready_message)

    def show_ready_message(self):
        self.set_string("Ready")
        self.master.after(750, self.show_fight_message)

    def show_fight_message(self):
        self.set_string("Fight !")
        self.master.after(900, self.hide)

    def end(self):
        self.show()
        self.finish_sound.play()
        self.set_string(str())
        self.master.after(300, self.show_finished_message)

    def show_finished_message(self):
        self.set_string("Finished")
        if self.winner is not None:
            self.master.after(1200, lambda: self.move_all_champions_up(0))

    def move_all_champions_up(self, index: int):
        if index < len(self.master.champions):
            champion = self.master.champions[index]
            champion.move_ip(0, -10)
            if index == 0:
                if champion.top <= 30:
                    index += 1
            else:
                champion_at_top = self.master.champions[index - 1]
                if champion.top <= champion_at_top.bottom + 30:
                    index += 1
            self.master.after(10, lambda i=index: self.move_all_champions_up(i))
        else:
            self.move_finished_message()

    def move_finished_message(self):
        self.move_ip(45, 0)
        if self.right < self.master.right - 20:
            self.master.after(10, self.move_finished_message)
        else:
            self.show_winner()

    def show_winner(self):
        winner = self.winner[self.winner.find("(") + 1:self.winner.find(")")] + "\nhas won."
        text = Text(winner, self.font, YELLOW)
        text.set_width(self.width)
        text.move(centerx=self.centerx, top=self.bottom + 10)
        self.master.add(text)

class Champion(Text):
    def __init__(self, file: str, name: str):
        Text.__init__(self, name, (FONT["death_star"], 80), YELLOW)
        self.assembly = file
        self.cor = os.path.splitext(file)[0] + ".cor"
        self.name = name

    def create(self) -> bool:
        cmd = [ASM, self.assembly]
        try:
            output_process = subprocess.run(cmd, check=True, capture_output=True)
        except subprocess.CalledProcessError as e:
            output = e.stderr.decode()
            status = e.returncode
        else:
            output = output_process.stderr.decode()
            status = output_process.returncode
        return bool(len(output) == 0 and status == 0)

    def live(self, status: bool):
        if status is True:
            self.set_string("Live - {name}".format(name=self.name))
        else:
            self.set_string(self.name)

class CoreWar:
    def __init__(self, champion_list: List[Champion]):
        self.champions = champion_list
        self.process = None

    def start(self):
        cmd = [COREWAR, "-g"] + [champion.cor for champion in self.champions]
        cmd = " ".join(cmd)
        self.process = subprocess.Popen(cmd, stdout=subprocess.PIPE, shell=True)

    def get_line(self):
        if self.process is not None:
            while True:
                line = self.process.stdout.readline().rstrip().decode()
                if not line and self.process.poll() is not None:
                    break
                yield line

    def kill(self):
        if self.process is not None and self.process.poll() is not None:
            self.process.terminate()
            self.process = None

class MemoryCase(RectangleShape):
    def __init__(self, master: Window, width: int, height: int, **kwargs):
        self.default_color = TRANSPARENT
        self.filled_color = BLUE_LIGHT
        RectangleShape.__init__(self, width, height, self.default_color, outline=1, **kwargs)
        master.add(self)
        self.__value = 0
        self.highlight = 0

    @property
    def value(self):
        return self.__value

    def set_value(self, byte: (int, str), base=10):
        highlight = 0
        if isinstance(byte, str):
            if byte[0] == "\033":
                highlight = int(byte[4:6])
                byte = remove_color_characters(byte)
        try:
            v = int(byte, base)
            if v == self.__value and highlight == self.highlight:
                return
            self.__value = v
            self.highlight = highlight
        except ValueError:
            return
        if self.value != 0:
            self.color = HIGHLIGHT_COLOR.get(highlight, self.filled_color)
        else:
            self.color = self.default_color

class Game(Window):
    def __init__(self, master: Window, champion_list: List[Tuple[str]]):
        Window.__init__(self, bg_music=AUDIO["battle"], bg_color=BLUE_DARK)
        self.bind_key(pygame.K_ESCAPE, lambda key: self.stop())
        loading_page = Loading(font=(FONT["death_star"], 270))
        loading_page.show(master)
        self.champions = list()
        self.not_created = list()
        for file, name in champion_list:
            champion = Champion(file, name)
            if not champion.create():
                self.not_created.append(name)
            else:
                self.champions.append(champion)
                self.add(champion)
        if len(self.not_created) == 0:
            self.memory_size = (0, 0)
            self.init_gameplay()
        else:
            msg = "\n".join(f" - {name} cannot be created" for name in self.not_created)
            msg += "\n" + "\n" + "Press Escape to return\nto the menu"
            self.error_message = Text(msg, (FONT["death_star"], 70), YELLOW, justify="center", center=self.center)
        loading_page.hide(self)

    def on_quit(self):
        self.corewar.kill()

    def init_gameplay(self):
        for i, champion in enumerate(self.champions):
            champion.color = HIGHLIGHT_COLOR[PLAYER_COLOR[i]]
        self.memory = list()
        self.corewar = CoreWar(self.champions)
        self.corewar.start()
        self.init_memory()
        self.animation = Animation(self)
        self.after(0, self.animation.start)

    def init_memory(self):
        nb_cols = 64
        nb_lines = MEMSIZE // nb_cols
        width = round(self.width / (2 * nb_cols))
        height = round((self.height - 100) / nb_lines)
        for i in range(MEMSIZE):
            case = MemoryCase(self, width, height)
            case.move(x=width * (i % nb_cols), y=height * (i // nb_cols))
            self.memory.append(case)
        self.memory_size = self.memory[-1].right - self.memory[0].left, self.memory[-1].bottom - self.memory[0].top
        for _, line in zip(range(len(self.memory)), self.corewar.get_line()):
            if re.match(r"^[0-9A-F]", line):
                self.set_line_memory(line)

    def set_line_memory(self, line: str):
        semicolon = line.find(":")
        address = int(line[:semicolon].strip(), 16)
        for byte in [hexa.strip() for hexa in line[semicolon + 1:].split()]:
            self.memory[address].set_value(byte, base=16)
            address += 1

    def update(self):
        if self.animation.is_shown():
            return
        line = next(self.corewar.get_line(), None)
        while line is not None and re.match(r"^[0-9A-F]", line):
            self.set_line_memory(line)
            line = next(self.corewar.get_line(), None)
        if line is None:
            self.animation.end()
        elif line.startswith("The player"):
            if line.endswith("has won."):
                self.animation.winner = str(line)
            else:
                player_id = int(line.split()[2]) - 1
                for i, champion in enumerate(self.champions):
                    if i == player_id:
                        champion.live(True)
                    else:
                        champion.live(False)

    def place_objects(self):
        if len(self.not_created) > 0:
            return
        centery = 0
        offset = round(self.height / (len(self.champions) + 1))
        for champion in self.champions:
            centery += offset
            champion.move(right=self.right - 20, centery=centery)