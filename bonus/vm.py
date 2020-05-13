#! /bin/python3
# -*- coding: Utf-8 -*

from constant import IMG, FONT
from my_pygame.window import Window
from my_pygame.colors import BLACK, BLUE_LIGHT, YELLOW, BLUE, BLUE_DARK
from my_pygame.classes import Image, Button
from loading import Loading
from game import GameMenu

class VmGame(Window):
    def __init__(self):
        Window.__init__(self)
        self.set_title("Corewar")
        loading_page = Loading(font=(FONT["death_star"], 270), opening=False, side_ending="right")
        loading_page.show(self)
        params_for_all_buttons = {
            "font": (FONT["death_star"], 120),
            "bg": BLUE,
            "hover_bg": BLUE_LIGHT,
            "active_bg": BLUE_DARK,
            "active_fg": YELLOW,
            "outline": 5,
            "outline_color": BLACK
        }
        self.bg = Image(IMG["menu_bg"], self.size)
        self.logo = Image(IMG["logo"], self.size)
        self.game_button = Button(self, "Game", command=self.play, **params_for_all_buttons)
        self.quit_button = Button(self, "Quit", command=self.stop, **params_for_all_buttons)
        self.place_objects()
        loading_page.hide(self)
        del loading_page

    def place_objects(self):
        self.bg.move(center=self.center)
        self.logo.move(center=self.center)
        self.game_button.move(centerx=self.centerx, centery=self.centery + 100)
        self.quit_button.move(centerx=self.centerx, top=self.game_button.bottom + 50)

    def play(self):
        game = GameMenu(self)
        game.mainloop()
        del game

def main():
    vm = VmGame()
    vm.mainloop()

if __name__ == "__main__":
    main()