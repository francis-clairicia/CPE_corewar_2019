# -*- coding: Utf-8 -*

import pygame
from constant import FONT, AUDIO
from my_pygame.window import Window
from my_pygame.colors import BLUE_LIGHT, YELLOW, BLUE, BLUE_DARK
from my_pygame.classes import RectangleShape, TextButton, Text, Scale

class Settings(Window):
    def __init__(self, master=None):
        Window.__init__(self, bg_color=None)
        if master is not None:
            self.bg = master.bg
        self.frame = RectangleShape(0.5 * self.w, 0.5 * self.h, BLUE, outline=3)
        self.title = Text("Settings", font=(FONT["death_star"], 50), color=YELLOW)
        params_for_all_scales = {
            "width": 0.7 * self.frame.w,
            "height": 50,
            "color": BLUE_DARK,
            "scale_color": BLUE_LIGHT,
            "from_": 0,
            "to": 100,
            "outline": 3
        }
        params_for_all_buttons = {
            "font": (FONT["death_star"], 45),
            "color": YELLOW,
            "hover_sound": AUDIO["clank"],
            "on_click_sound": AUDIO["laser"],
        }
        self.scale_sound_volume = Scale(
            self, **params_for_all_scales, default=Window.sound_volume() * 100,
            command=self.update_sound_volume
        )
        self.scale_music_volume = Scale(
            self, **params_for_all_scales, default=Window.music_volume() * 100,
            command=self.update_music_volume
        )
        self.button_return = TextButton(self, "Return", **params_for_all_buttons, command=self.stop)
        self.bind_key(pygame.K_ESCAPE, lambda key: self.stop())

    def place_objects(self):
        self.frame.move(center=self.center)
        self.title.move(top=self.frame.top + 10, centerx=self.frame.centerx)
        self.scale_sound_volume.move(top=self.title.bottom + 100, centerx=self.frame.centerx)
        self.scale_sound_volume.show_label("Sound", (FONT["death_star"], 45), YELLOW, Scale.S_TOP)
        self.scale_sound_volume.show_value((FONT["death_star"], 45), YELLOW, Scale.S_INSIDE)
        self.scale_music_volume.move(top=self.scale_sound_volume.bottom + 70, centerx=self.frame.centerx)
        self.scale_music_volume.show_label("Music", (FONT["death_star"], 45), YELLOW, Scale.S_TOP)
        self.scale_music_volume.show_value((FONT["death_star"], 45), YELLOW, Scale.S_INSIDE)
        self.button_return.move(bottom=self.frame.bottom - 10, centerx=self.frame.centerx)

    def update_sound_volume(self):
        Window.set_sound_volume(self.scale_sound_volume.percent)

    def update_music_volume(self):
        Window.set_music_volume(self.scale_music_volume.percent)