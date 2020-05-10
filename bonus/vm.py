#! /bin/python3
# -*- coding: Utf-8 -*

from constant import IMG
from my_pygame.window import Window
from my_pygame.colors import BLACK, BLUE_LIGHT, YELLOW, BLUE, BLUE_DARK
from my_pygame.classes import Image, Button
from loading import Loading

class VmGame(Window):
    def __init__(self):
        Window.__init__(self)
        loading_page = Loading(opening=False, side_ending="right")
        loading_page.show(self)
        self.set_title("Corewar")
        params_for_all_buttons = {
            "font": ("calibiri", 200),
            "bg": BLUE,
            "over_bg": BLUE_DARK,
            "active_bg": BLUE_LIGHT,
            "over_fg": YELLOW,
            "outline": 5,
            "outline_color": BLACK
        }
        self.bg = Image(IMG["menu_bg"], self.window_rect.size)
        self.logo = Image(IMG["logo"], self.window_rect.size)
        self.game_button = Button(self, "Game", **params_for_all_buttons)
        self.quit_button = Button(self, "Quit", command=self.stop, **params_for_all_buttons)
        self.place_objects()
        loading_page.hide(self)

    def place_objects(self):
        self.bg.move(center=self.window_rect.center)
        self.logo.move(center=self.window_rect.center)
        self.game_button.move(centerx=self.window_rect.centerx, centery=self.window_rect.centery + 100)
        self.quit_button.move(centerx=self.window_rect.centerx, top=self.game_button.bottom + 50)

def main():
    vm = VmGame()
    vm.mainloop()

if __name__ == "__main__":
    main()