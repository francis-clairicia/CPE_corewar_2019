# -*- coding: Utf-8 -*

from constant import FONT, AUDIO
from my_pygame import Window, Button, Text
from my_pygame.colors import BLUE_LIGHT, YELLOW, BLUE, BLUE_DARK
from editor import Editor
from battle import Battle

class GameMenu(Window):
    def __init__(self, master: Window):
        Window.__init__(self)
        self.bg = master.bg
        self.title = Text("Game", font=(FONT["death_star"], 220), color=YELLOW)
        params_for_all_buttons = {
            "bg": BLUE,
            "hover_bg": BLUE_LIGHT,
            "active_bg": BLUE_DARK,
            "active_fg": YELLOW,
            "hover_sound": AUDIO["clank"],
            "on_click_sound": AUDIO["laser"],
            "outline": 5,
        }
        params_for_section_button = {
            "font": (FONT["death_star"], 200)
        }
        self.button_battle = Button(self, "Battle", **params_for_all_buttons, **params_for_section_button, command=self.launch_battle)
        self.button_edit = Button(self, "Editor", **params_for_all_buttons, **params_for_section_button, command=self.launch_editor)
        self.button_menu = Button(self, "Menu", **params_for_all_buttons, font=(FONT["death_star"], 80), command=self.stop)

    def place_objects(self):
        self.title.move(centerx=self.centerx, top=10)
        self.button_battle.move(centerx=self.centerx - (self.w // 4), centery=self.centery)
        self.button_edit.move(centerx=self.centerx + (self.w // 4), centery=self.centery)
        self.button_menu.move(centerx=self.centerx, bottom=self.bottom - 100)

    def launch_editor(self):
        Editor(self).mainloop()

    def launch_battle(self):
        Battle(self).mainloop()