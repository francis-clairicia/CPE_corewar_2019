# -*- coding: Utf-8 -*

import os
import tkinter as tk
from constants import HELP_FOLDER, MNEMONICS

class Manual(tk.Toplevel):
    def __init__(self, master, *args, **kwargs):
        tk.Toplevel.__init__(self, master, *args, **kwargs, takefocus=True)
        self.master = master
        width = 500
        height = 200
        self.protocol("WM_DELETE_WINDOW", self.close)
        self.resizable(width=False, height=False)
        self.title("Assemby manual")
        self.transient(master)
        self.contents = dict()
        self.message = tk.StringVar()
        self.list = tk.Listbox(self, selectmode=tk.SINGLE, font=("", 12))
        self.list.bind("<<ListboxSelect>>", lambda event: self.on_select())
        self.list.grid(row=0, column=0, padx=10, pady=10, sticky=tk.NW)
        self.message_box = tk.Message(self, aspect=200, textvariable=self.message, font=("", 10))
        self.message_box.grid(row=0, column=1, sticky=tk.NW)
        self.grid_columnconfigure(1, minsize=int(width * 0.7), weight=1)
        self.grid_rowconfigure(0, minsize=height)
        for name in MNEMONICS:
            path = os.path.join(HELP_FOLDER, name + ".txt")
            if os.path.isfile(path):
                with open(path, "r") as file:
                    self.contents[name] = file.read()
                self.list.insert(tk.END, name)
        self.list.configure(height=self.list.size(), width=len(max(self.contents.keys(), key=lambda e: len(e))) + 2)

    def close(self):
        self.master.manual = None
        self.destroy()

    def on_select(self):
        try:
            name = self.list.get(self.list.curselection()[0])
        except IndexError:
            pass
        else:
            self.message.set(f"Mnemonic {name}\n\n" + self.contents[name])