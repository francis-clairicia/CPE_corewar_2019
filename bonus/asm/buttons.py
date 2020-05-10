# -*- coding: Utf-8 -*

import os
import tkinter as tk
from color import Color
from constants import IMG_FOLDER
from tooltip import create_tooltip

class IconButton(tk.Button):
    def __init__(self, master, icon, tooltip=None, **kwargs):
        self.icon = tk.PhotoImage(file=os.path.join(IMG_FOLDER, icon))
        tk.Button.__init__(self, master, bg=master["bg"], image=self.icon, **kwargs)
        self.configure(activebackground=self["bg"], highlightbackground=self["bg"], cursor="hand1")
        self.change_contrast_active(10)
        if tooltip is not None:
            create_tooltip(self, tooltip)

    def change_contrast_active(self, offset):
        color = Color.from_hex(self.cget("activebackground"))
        color.v += offset
        self.configure(activebackground=color.hex)