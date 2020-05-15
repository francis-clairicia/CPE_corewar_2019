# -*- coding: Utf-8 -*

import tkinter as tk
from constants import PROG_NAME_LENGTH, COMMENT_LENGTH

class ChampionEntry(tk.Frame):
    def __init__(self, master, max_size: int, *args, **kwargs):
        tk.Frame.__init__(self, master)
        self.max_size = max_size
        self.entry = tk.Entry(self, *args, **kwargs)
        self.entry.configure(validate="key", validatecommand=(self.register(self.validation_entry), "%P"))
        self.scrollbar = tk.Scrollbar(self, orient=tk.HORIZONTAL, command=self.entry.xview)
        self.entry.configure(xscrollcommand=self.scrollbar.set)
        self.entry.grid()
        self.scrollbar.grid(row=1, sticky=tk.EW)

    def get(self) -> str:
        return self.entry.get()

    def validation_entry(self, value: str) -> bool:
        return bool(self.max_size < 0 or len(value) <= self.max_size)

class Template(tk.Toplevel):
    def __init__(self, master, *args, **kwargs):
        tk.Toplevel.__init__(self, master, *args, takefocus=True, **kwargs)
        self.transient(master)
        self.resizable(width=False, height=False)
        self.title("Starting template for champion")
        self.lift()
        self.grab_set()

        self.font = ("", 15)
        self.label_name = tk.Message(self, aspect=300, text=f"Champion name\n({PROG_NAME_LENGTH} chars max)", font=self.font)
        self.name = ChampionEntry(self, max_size=PROG_NAME_LENGTH, width=20, font=self.font)
        self.label_comment = tk.Message(self, aspect=300, text=f"Comment about him\n({COMMENT_LENGTH} chars max)", font=self.font)
        self.comment = ChampionEntry(self, max_size=COMMENT_LENGTH, width=20, font=self.font)
        self.label_author = tk.Label(self, text="Author", font=self.font)
        self.author = ChampionEntry(self, max_size=-1, width=20, font=self.font)
        self.button_validation = tk.Button(self, text="Validate", font=self.font, command=self.on_validation)

        self.label_name.grid(row=0, column=0, padx=10, pady=10, sticky=tk.W)
        self.name.grid(row=0, column=1, padx=10, pady=10)
        self.label_comment.grid(row=1, column=0, padx=10, pady=10, sticky=tk.W)
        self.comment.grid(row=1, column=1, padx=10, pady=10)
        self.label_author.grid(row=2, column=0, padx=10, pady=10, sticky=tk.W)
        self.author.grid(row=2, column=1, padx=10, pady=10)
        self.button_validation.grid(row=3, column=0, columnspan=2)

        self.name.entry.bind("<KeyRelease-Return>", lambda event: self.comment.entry.focus_set())
        self.comment.entry.bind("<KeyRelease-Return>", lambda event: self.author.entry.focus_set())
        self.author.entry.bind("<KeyRelease-Return>", lambda event: self.button_validation.focus_set())
        self.button_validation.bind("<KeyRelease-Return>", lambda event: self.button_validation.invoke())

        self.validated = False

    def on_validation(self):
        self.validated = True
        self.name = self.name.get()
        self.comment = self.comment.get()
        self.author = self.author.get()
        self.destroy()