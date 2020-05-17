# -*- coding: Utf-8 -*

import os
import subprocess
from threading import Thread
import pygame
from constant import FONT, AUDIO, CHAMPIONS_FOLDER, EDITOR
from my_pygame import Window, Text, TextButton, RectangleShape
from my_pygame.colors import YELLOW, BLUE_DARK
from my_pygame import Loading
from utils import get_champion_name

class ChampionEditor(TextButton):
    def __init__(self, master: Window, assembly_file: str, *args, **kwargs):
        TextButton.__init__(self, master, *args, **kwargs, command=lambda self=self: master.launch_assembly_editor(self.file))
        self.file = assembly_file
        master.bind_event(pygame.MOUSEBUTTONUP, self.delete)

    def delete(self, event):
        if event.button == 3 and self.rect.collidepoint(event.pos):
            os.remove(self.file)
            binary = os.path.splitext(self.file)[0] + ".cor"
            if os.path.isfile(binary):
                os.remove(binary)
            self.callback = None

    def update_file(self, new_file: str, new_name: str):
        self.file = new_file
        self.set_text(new_name)

class Editor(Window):
    def __init__(self, master: Window):
        Window.__init__(self, bg_color=BLUE_DARK, bg_music=AUDIO["dark_techno_city"])
        loading_page = Loading(font=(FONT["death_star"], 270))
        loading_page.show(master)
        self.title = Text("Editor", font=(FONT["death_star"], 150), color=YELLOW)
        self.subtitle = Text("Choose the champion to edit", font=(FONT["death_star"], 70), color=YELLOW)
        self.params_for_all_buttons = {
            "font": (FONT["death_star"], 80),
            "color": YELLOW,
            "hover_fg": (255, 255, 128),
            "hover_sound": AUDIO["clank"],
            "on_click_sound": AUDIO["laser"],
            "outline": 2,
            "outline_color": YELLOW,
            "offset": 6,
        }
        self.button_menu = TextButton(self, "Menu", **self.params_for_all_buttons, command=self.stop)
        self.champions = list()
        champion_files = sorted(os.path.join(CHAMPIONS_FOLDER, file) for file in os.listdir(CHAMPIONS_FOLDER) if file.endswith(".s"))
        for file in champion_files:
            name = get_champion_name(file)
            champion = ChampionEditor(self, file, name, **self.params_for_all_buttons)
            self.champions.append(champion)
            self.add(champion)
        self.new_file = TextButton(self, "New", **self.params_for_all_buttons, command=self.launch_assembly_editor)
        self.editors = list()
        self.bind_key(pygame.K_ESCAPE, lambda key: self.stop())
        loading_page.hide(self)

    def update(self):
        self.check_process()
        champion_files = sorted(os.path.join(CHAMPIONS_FOLDER, file) for file in os.listdir(CHAMPIONS_FOLDER) if file.endswith(".s"))
        for champion in self.champions:
            try:
                champion_files.index(champion.file)
            except ValueError:
                self.remove(champion)
                self.champions.remove(champion)
        for i, file in enumerate(champion_files):
            name = get_champion_name(file)
            if i in range(len(self.champions)):
                self.champions[i].update_file(file, name)
            else:
                champion = ChampionEditor(self, file, name, **self.params_for_all_buttons)
                self.champions.append(champion)
                self.add(champion)
        self.place_champions()

    def check_process(self):
        for process in self.editors:
            if not process.is_alive():
                self.editors.remove(process)

    def place_objects(self):
        self.title.move(centerx=self.centerx, top=10)
        self.subtitle.move(centerx=self.centerx, top=self.title.bottom + 10)
        self.button_menu.move(bottom=self.bottom - 50, right=self.right - 10)
        self.place_champions()
        self.new_file.move(right=self.right - 10, top=10)

    def place_champions(self):
        rect = pygame.Rect(0, self.subtitle.bottom + 50, 0, 10)
        for champion in self.champions:
            rect = champion.move(top=rect.top, left=rect.right + 30)
            if rect.right >= self.right - 10:
                rect = champion.move(top=rect.bottom + 10, left=40)

    def on_quit(self):
        if len(self.editors) > 0:
            bg = RectangleShape(self.w, self.h, (0, 0, 0, 128))
            bg.draw(self.window)
            text = Text("Waiting for you to close all the editors", (FONT["death_star"], 70), YELLOW)
            text.move(center=self.center)
            text.draw(self.window)
            self.refresh()
            while len(self.editors) > 0:
                self.check_process()
                self.main_clock.tick(self.fps)
                pygame.event.pump()

    def launch_assembly_editor(self, file=None):
        if file is not None:
            cmd = [EDITOR, file, "--no-workspace"]
        else:
            cmd = [EDITOR, "--no-workspace", "-d", CHAMPIONS_FOLDER]
        process = Thread(target=subprocess.run, args=(cmd,), kwargs={"check": False, "capture_output": True})
        process.start()
        self.editors.append(process)