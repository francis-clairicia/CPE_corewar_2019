# -*- coding: Utf-8 -*

import os
import random
import textwrap
import pygame
from constant import IMG, FONT, AUDIO, CHAMPIONS_FOLDER, MAX_NB_PLAYERS
from my_pygame import Window, Text, TextButton, RectangleShape, Image, Button
from my_pygame.colors import YELLOW, BLUE_DARK, BLUE, BLUE_LIGHT
from loading import Loading
from game import Game
from utils import get_champion_name, get_champion_comment

class ChampionViewer(TextButton):
    def __init__(self, master, assembly_file: str, *args, **kwargs):
        TextButton.__init__(self, master, *args, **kwargs, command=self.select)
        self.file = assembly_file
        self.master = master
        self.comment = get_champion_comment(assembly_file)
        self.selected = False
        self.select_img = Image(IMG["valide"])
        self.select_img.hide()
        master.add(self.select_img)

    def hide_all(self):
        self.hide()
        self.select_img.hide()

    def update(self, *args, **kwargs):
        self.select_img.move(left=self.right + 10, centery=self.centery)

    def select(self):
        self.selected = not self.selected
        if self.selected:
            if len(self.master.selected) >= MAX_NB_PLAYERS:
                self.selected = False
                return
            self.select_img.show()
            self.master.selected.append(self)
        else:
            self.select_img.hide()
            try:
                self.master.selected.remove(self)
            except ValueError:
                pass

    def update_file(self, new_file: str, new_name: str):
        self.file = new_file
        self.set_text(new_name)
        self.comment = get_champion_comment(new_file)

class Infos(RectangleShape):
    def __init__(self, master, *args, **kwargs):
        RectangleShape.__init__(self, *args, **kwargs)
        self.prog_name = Text(str(), (FONT["death_star"], 80), YELLOW, justify="center")
        self.prog_comment = Text(str(), (FONT["death_star"], 80), YELLOW, justify="center")
        self.infos_nb_selected = Text(f"0/{MAX_NB_PLAYERS}", (FONT["death_star"], 80), YELLOW)
        params_button = {
            "bg": BLUE,
            "hover_bg": BLUE_LIGHT,
            "active_bg": BLUE_DARK,
            "active_fg": YELLOW,
            "hover_sound": AUDIO["clank"],
            "on_click_sound": AUDIO["laser"],
            "outline": 5,
        }
        self.button_battle = Button(master, "Play", font=(FONT["death_star"], 80), **params_button, command=master.launch_game)
        self.default_width = 0

    def draw(self, surface):
        if self.is_shown():
            self.draw_shape(surface)
            self.prog_name.draw(surface)
            self.prog_comment.draw(surface)
            self.infos_nb_selected.draw(surface)
            self.button_battle.draw(surface)

    def hide_all(self):
        for obj in [self.prog_name, self.prog_comment, self.infos_nb_selected, self.button_battle]:
            obj.hide()

    def update(self, *args, **kwargs):
        self.prog_name.move(centerx=self.centerx, bottom=self.centery - 70)
        self.prog_comment.move(centerx=self.centerx, top=self.prog_name.centery + 70)
        self.infos_nb_selected.move(left=self.left + 10, bottom=self.bottom - 10)
        self.button_battle.move(centerx=self.centerx, bottom=self.bottom - 10)

    def update_nb_selected(self, nb):
        self.infos_nb_selected.set_string(f"{nb}/{MAX_NB_PLAYERS}")

    def show_infos(self, name: str, comment: str):
        self.prog_name.set_string("Name : " + str(name))
        self.prog_comment.set_string(comment)
        self.default_width = self.width - 30
        for obj in [self.prog_name, self.prog_comment]:
            length = len(obj.get_string())
            while obj.width > self.default_width:
                length -= 1
                obj.set_string(textwrap.fill(comment, width=length))

    def clear_frame(self):
        self.prog_name.set_string(str())
        self.prog_comment.set_string(str())

class Battle(Window):
    def __init__(self, master: Window):
        Window.__init__(self, bg_color=BLUE_DARK, bg_music=AUDIO["crusaders"])
        loading_page = Loading(font=(FONT["death_star"], 270))
        loading_page.show(master)
        self.bg_title = RectangleShape(self.width, self.height, self.bg_color)
        self.title = Text("Battle", font=(FONT["death_star"], 150), color=YELLOW)
        self.subtitle = Text("Choose your champions for the fight", font=(FONT["death_star"], 70), color=YELLOW)
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
            champion = ChampionViewer(self, file, name, **self.params_for_all_buttons)
            self.champions.append(champion)
            self.add(champion)
        self.selected = list()
        self.start_champion = 0
        self.move_champion_up = False
        self.move_champion_down = False
        self.infos = Infos(self, 1, 1, self.bg_color, outline=3, outline_color=YELLOW)
        self.bind_key(pygame.K_ESCAPE, lambda key: self.stop())
        self.bind_event(pygame.MOUSEBUTTONDOWN, self.move_champion_list)
        loading_page.hide(self)

    def update(self):
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
                champion = ChampionViewer(self, file, name, **self.params_for_all_buttons)
                self.champions.append(champion)
                self.add(champion)
        for obj in [self.bg_title, self.title, self.subtitle]:
            self.set_object_priority(obj, self.end_list)
        self.place_champions()
        self.infos.clear_frame()
        for champion in self.champions:
            champion.update()
            if champion.hover:
                self.infos.show_infos(champion.get_text(), champion.comment)
        self.infos.update_nb_selected(len(self.selected))
        self.infos.update()

    def place_objects(self):
        self.title.move(centerx=self.centerx, top=10)
        self.subtitle.move(centerx=self.centerx, top=self.title.bottom + 10)
        self.button_menu.move(bottom=self.bottom - 50, right=self.right - 10)
        self.bg_title.set_size(self.width, self.subtitle.bottom + 10)
        self.start_champion = self.subtitle.bottom + 40
        self.bg_title.color = self.bg_color
        self.infos.set_size((self.w / 2) - 10, self.button_menu.top - self.subtitle.bottom - (10 * 2))
        self.infos.move(top=self.subtitle.bottom + 10)
        self.place_champions()
        self.infos.update()

    def place_champions(self):
        rect = pygame.Rect(0, self.start_champion, 0, 0)
        for champion in self.champions:
            rect = champion.move(top=rect.bottom + 10, left=10)
        self.move_champion_up = bool(rect.bottom >= self.button_menu.bottom)
        self.move_champion_down = bool(self.start_champion < self.subtitle.bottom + 40)
        self.infos.move(centerx=self.centerx)
        self.infos.move(x=max([self.infos.left, max(champion.right + 20 for champion in self.champions)]))

    def move_champion_list(self, event):
        if event.button == 4:
            if self.move_champion_down:
                self.start_champion += 10
        elif event.button == 5:
            if self.move_champion_up:
                self.start_champion -= 10

    def launch_game(self, animation=True):
        if len(self.selected) < 2:
            return
        if animation:
            self.infos.hide_all()
            self.button_menu.hide()
            hiding_frame = RectangleShape(self.infos.left - 10 - self.left, self.height, self.bg_color)
            hiding_frame.move(x=0, bottom=self.bg_title.bottom)
            self.add(hiding_frame)
            self.hide_champions(hiding_frame)
        else:
            champions_list = [(champion.file, champion.get_text()) for champion in self.selected]
            random.shuffle(champions_list)
            game = Game(self, champions_list)
            game.mainloop()
            self.stop()

    def hide_champions(self, hiding_frame: RectangleShape):
        hiding_frame.move_ip(0, 10)
        for champion in self.champions:
            if champion.bottom <= hiding_frame.bottom:
                champion.hide_all()
        if hiding_frame.top < 0:
            self.after(10, lambda frame=hiding_frame: self.hide_champions(frame))
        else:
            for champion in self.champions:
                if champion.is_shown():
                    champion.hide_all()
            text = self.draw_selected_champions()
            hiding_frame.set_size(self.infos.width - 5, self.infos.height - 5, smooth=False)
            hiding_frame.move(centerx=self.centerx, bottom=self.infos.bottom - 5)
            self.set_object_priority(hiding_frame, 1, relative_to=text)
            self.show_selected_champions(hiding_frame)

    def draw_selected_champions(self):
        selected = "\n".join(f"{i + 1} - {champion.get_text()}" for i, champion in enumerate(self.selected))
        for _ in range(len(self.selected), MAX_NB_PLAYERS + 2):
            selected += "\n"
        selected += "Let's play !"
        text = Text(selected, (FONT["death_star"], 80), YELLOW)
        length = len(selected)
        while text.width > self.infos.default_width:
            length -= 1
            text.set_string(textwrap.fill(selected, width=length))
        text.move(centerx=self.infos.centerx, top=self.infos.top + 10)
        self.add(text)
        return text

    def show_selected_champions(self, hiding_frame: RectangleShape):
        hiding_frame.set_size(hiding_frame.width, hiding_frame.height - 10, smooth=False)
        if hiding_frame.is_shown():
            self.after(10, lambda frame=hiding_frame: self.show_selected_champions(frame))
        else:
            self.after(1000, lambda animation=False: self.launch_game(animation))