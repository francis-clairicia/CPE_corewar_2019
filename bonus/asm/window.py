# -*- coding: Utf-8 -*

import os
import sys
import subprocess
import tkinter as tk
from tkinter.messagebox import showinfo, showerror
from editor import Editor
from buttons import IconButton
from command_list import CommandList
from manual import Manual
from utils import remove_color_characters

class MenuWindow(tk.Menu):
    def __init__(self, master, *args, **kwargs):
        tk.Menu.__init__(self, *args, **kwargs)
        master.config(menu=self)
        self.sections = dict()

    def add_section(self, name: str):
        if name not in self.sections:
            self.sections[name] = tk.Menu(self, tearoff=0, font=("", 12))
            self.add_cascade(label=name, menu=self.sections[name])

    def add_section_command(self, section: str, name: str, command, **kwargs):
        if section in self.sections:
            self.sections[section].add_command(label=name, command=command, **kwargs)

    def add_section_separator(self, section: str):
        if section in self.sections:
            self.sections[section].add_separator()

class Assembly(tk.Tk):
    def __init__(self, title: str, width: int, height: int):
        tk.Tk.__init__(self)
        self.title(title)
        self.geometry(f"{width}x{height}+0+0")
        self.minsize(width, height)
        self.protocol("WM_DELETE_WINDOW", self.stop)

        self.menu_bar = MenuWindow(self, font=("", 12))

        self.paned_window = tk.PanedWindow(self, orient=tk.HORIZONTAL, sashwidth=5, sashrelief=tk.RAISED)
        self.paned_window.bind("<Configure>", self.set_panedwindow_size)

        self.editor = Editor(self, width=int(width * 0.7))

        self.options = tk.Frame(self, width=int(width * 0.3))
        self.build = IconButton(self.options, "build.png", tooltip="Build champion", command=self.build_code)
        self.template = IconButton(self.options, "template.png", tooltip="Start with template", command=self.editor.start_template)
        self.help = IconButton(self.options, "help.png", tooltip="Manual for help", command=self.open_manual)
        self.manual = None
        self.command_list = CommandList(self.options)
        self.command_list.button_add.configure(command=self.add_command)

        self.paned_window.add(self.options)
        self.paned_window.add(self.editor)

        self.menu_bar.add_section("Files")
        self.menu_bar.add_section_command("Files", "New file", self.editor.create_new_file, accelerator="Ctrl+N")
        self.menu_bar.add_section_command("Files", "Open file", self.editor.open_file, accelerator="Ctrl+O")
        self.menu_bar.add_section_separator("Files")
        self.menu_bar.add_section_command("Files", "Save", self.editor.save_in_file, accelerator="Ctrl+S")
        self.menu_bar.add_section_command("Files", "Save All", self.editor.save_all_files, accelerator="Ctrl+Shift+S")
        self.menu_bar.add_section_command("Files", "Save As", self.editor.save_file_as, accelerator="Alt+Ctrl+S")
        self.menu_bar.add_section_separator("Files")
        self.menu_bar.add_section_command("Files", "Close", self.editor.close_file, accelerator="Ctrl+W")
        self.menu_bar.add_section_command("Files", "Close All", self.editor.close_all_files, accelerator="Ctrl+Shift+W")
        self.menu_bar.add_section_separator("Files")
        self.menu_bar.add_section_command("Files", "Exit", self.stop, accelerator="[Alt+F4 Ctrl+Q]")
        self.menu_bar.add_section("Edit")
        self.menu_bar.add_section_command("Edit", "Undo", self.editor.undo_last_modification, accelerator="Ctrl+Z")
        self.menu_bar.add_section_command("Edit", "Redo", self.editor.redo_last_undo, accelerator="Ctrl+Shift+Z")
        self.menu_bar.add_section_separator("Edit")
        self.menu_bar.add_section_command("Edit", "Cut", self.editor.cut_to_clipboard, accelerator="Ctrl+X")
        self.menu_bar.add_section_command("Edit", "Copy", self.editor.copy_to_clipboard, accelerator="Ctrl+C")
        self.menu_bar.add_section_command("Edit", "Paste", self.editor.paste_from_clipboard, accelerator="Ctrl+V")

        self.refresh_functions = list()
        self.refresh_functions.append(self.editor.update_tab)

    def run(self, file=None):
        if file is not None:
            self.editor.open_file(file)
        self.all_binds()
        self.show_widgets()
        self.refresh()
        self.mainloop()

    def stop(self):
        if self.editor.close_workspace():
            self.destroy()

    def show_widgets(self):
        self.paned_window.pack(fill=tk.BOTH, expand=True)
        self.options.grid_columnconfigure(0, weight=1)
        self.options.grid_columnconfigure(1, weight=1)
        self.options.grid_columnconfigure(2, weight=1)
        self.build.grid(row=0, column=0, pady=20)
        self.template.grid(row=0, column=1, pady=20)
        self.help.grid(row=0, column=2, pady=20)
        self.command_list.grid(row=1, column=0, columnspan=3)

    def refresh(self):
        for function in self.refresh_functions:
            function()
        self.after(10, self.refresh)

    def all_binds(self):
        self.bind_key("Control", "n", lambda event: self.editor.create_new_file())
        self.bind_key("Control", "o", lambda event: self.editor.open_file())
        self.bind_key("Control", "s", lambda event: self.editor.save_in_file())
        self.bind_key("Control-Shift", "s", lambda event: self.editor.save_all_files())
        self.bind_key("Control-Alt", "s", lambda event: self.editor.save_file_as())
        self.bind_key("Control", "w", lambda event: self.editor.close_file())
        self.bind_key("Control-Shift", "w", lambda event: self.editor.close_all_files())
        self.bind_key("Control", "q", lambda event: self.stop())

    def bind_key(self, modifiers: str, key: str, command):
        self.bind_all(f"<{modifiers}-{key.lower()}>", command)
        self.bind_all(f"<{modifiers}-{key.upper()}>", command)

    def set_panedwindow_size(self, event):
        self.paned_window.paneconfigure(self.options, minsize=0.3 * event.width)
        self.paned_window.paneconfigure(self.editor, minsize=0.5 * event.width)
        self.editor.configure(width=int(event.width * 0.7))
        self.options.configure(width=int(event.width * 0.3))

    def build_code(self):
        filepath = self.editor.get_file()
        if len(filepath) == 0:
            return
        cmd = [os.path.join(sys.path[0], "asm_compiler"), filepath]
        try:
            output_process = subprocess.run(cmd, check=True, capture_output=True)
        except subprocess.CalledProcessError as e:
            output = e.stderr.decode()
            status = e.returncode
        else:
            output = output_process.stderr.decode()
            status = output_process.returncode
        if len(output) == 0 and status == 0:
            showinfo("Compilation completed", "The compilation was a succes !")
        else:
            output = remove_color_characters(output)[:-1]
            showerror("An error occurs", output.split(", ")[2])

    def add_command(self):
        command = self.command_list.selected
        if command is None:
            return
        self.editor.insert_command(command.get())
        self.command_list.reset()

    def open_manual(self):
        if self.manual is None:
            self.manual = Manual(self)
        else:
            self.manual.focus_set()