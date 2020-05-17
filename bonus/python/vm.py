#! /bin/python3
# -*- coding: Utf-8 -*

import pygame
from constant import IMG, FONT, AUDIO
from my_pygame import Window, Image, Button, ImageButton
from my_pygame.colors import BLUE_LIGHT, YELLOW, BLUE, BLUE_DARK
from loading import Loading
from menu import GameMenu
from settings import Settings

class VmGame(Window):
    def __init__(self):
        Window.__init__(self, bg_music=AUDIO["ancient_game_open"], flags=pygame.NOFRAME)
        self.set_title("Corewar")
        loading_page = Loading(font=(FONT["death_star"], 270), opening=False)
        loading_page.show(self)
        params_for_all_buttons = {
            "font": (FONT["death_star"], 120),
            "bg": BLUE,
            "hover_bg": BLUE_LIGHT,
            "active_bg": BLUE_DARK,
            "hover_sound": AUDIO["clank"],
            "on_click_sound": AUDIO["laser"],
            "active_fg": YELLOW,
            "outline": 5,
        }
        self.bg = Image(IMG["menu_bg"], self.size)
        self.logo = Image(IMG["logo"], self.size)
        self.game_button = Button(self, "Game", command=GameMenu(self).mainloop, **params_for_all_buttons)
        self.quit_button = Button(self, "Quit", command=self.stop, **params_for_all_buttons)
        build_img = Image(IMG["build"], size=100)
        self.settings_button = ImageButton(self, build_img, show_bg=True, command=Settings(self).mainloop, **params_for_all_buttons)
        loading_page.hide(self)

    def place_objects(self):
        self.bg.move(center=self.center)
        self.logo.move(center=self.center)
        self.game_button.move(centerx=self.centerx, centery=self.centery + 100)
        self.quit_button.move(centerx=self.centerx, top=self.game_button.bottom + 50)
        self.settings_button.move(x=20, y=20)

def main():
    vm = VmGame()
    vm.mainloop()

if __name__ == "__main__":
    main()