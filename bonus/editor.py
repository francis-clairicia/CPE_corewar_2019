# -*- coding: Utf-8 -*

import pygame
from constant import FONT, AUDIO
from my_pygame.window import Window
from my_pygame.colors import YELLOW, BLUE_DARK
from my_pygame.classes import Text, TextButton
from loading import Loading

class Editor(Window):
    def __init__(self, master: Window):
        Window.__init__(self, bg_color=BLUE_DARK, bg_music=AUDIO["dark_techno_city"])
        loading_page = Loading(font=(FONT["death_star"], 270), side_ending="right")
        loading_page.show(master)
        self.title = Text("Editor", font=(FONT["death_star"], 150), color=YELLOW)
        self.subtitle = Text("Choose the champion to edit", font=(FONT["death_star"], 70), color=YELLOW)
        params_for_all_buttons = {
            "font": (FONT["death_star"], 50),
            "color": YELLOW,
            "hover_fg": (255, 255, 128),
            "hover_sound": AUDIO["clank"],
            "on_click_sound": AUDIO["laser"],
            "outline": 2,
            "outline_color": YELLOW,
            "offset": 5,
        }
        self.button_menu = TextButton(self, "Menu", **params_for_all_buttons, command=self.stop)
        self.bind_key(pygame.K_ESCAPE, lambda key: self.stop())
        loading_page.hide(self)

    def place_objects(self):
        self.title.move(centerx=self.centerx, top=10)
        self.subtitle.move(centerx=self.centerx, top=self.title.bottom + 10)
        self.button_menu.move(bottom=self.bottom - 50, right=self.right - 10)
