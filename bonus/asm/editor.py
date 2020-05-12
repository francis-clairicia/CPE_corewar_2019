#-*- coding: Utf-8 -*

import os
import pickle
from datetime import date
import tkinter as tk
from tkinter import ttk
from tkinter.scrolledtext import ScrolledText
from tkinter.messagebox import showwarning, askyesnocancel
from tkinter.filedialog import askopenfilename, asksaveasfilename
from template import Template
from color import Color
from constants import EDITOR_SAVE_FILE
from utils import get_filename

class EditorTab(tk.Frame):
    def __init__(self, master, filepath: str, new_file=False):
        tk.Frame.__init__(self, master)
        self.new_file = new_file
        self.filepath = filepath
        self.filename = get_filename(filepath) if not new_file else filepath
        self.master = master
        self.modified = False
        self.text_editor = ScrolledText(self, font=("", 15), undo=True, maxundo=-1, wrap="none")
        self.text_editor.config(highlightthickness=0, bd=0)
        self.text_editor.grid(row=0, column=1, sticky=tk.NSEW)
        self.scrollbar_x = tk.Scrollbar(self, orient=tk.HORIZONTAL, command=self.text_editor.xview)
        self.scrollbar_x.grid(row=1, column=0, columnspan=2, stick=tk.EW)
        self.text_editor.configure(xscrollcommand=self.scrollbar_x.set)
        self.line_nb_canvas = tk.Canvas(self, bg=self.text_editor.cget("bg"), bd=0, highlightthickness=0)
        self.line_nb_canvas.grid_propagate(False)
        self.line_nb_canvas.grid(row=0, column=0, sticky=tk.NS)
        self.grid_rowconfigure(0, weight=1)
        self.grid_columnconfigure(1, weight=1)
        self.default_file_content = str()

    @property
    def id(self) -> str:
        return str(self)

    def get(self) -> str:
        return self.text_editor.get("1.0", "end-1c")

    @property
    def lines(self):
        return self.get().splitlines()

    def update_lines(self):
        self.line_nb_canvas.delete("all")
        font = self.text_editor.cget("font")
        i = 1
        y = 0
        while self.text_editor.compare(f"{i}.0", "<", tk.END):
            dline = self.text_editor.dlineinfo(f"{i}.0")
            if dline:
                y = dline[1]
            else:
                y = -20
            self.line_nb_canvas.create_text(1, y, anchor="ne", text=str(i), font=font, fill=Color(175, 175, 175).hex)
            i += 1
        all_boxes = [self.line_nb_canvas.bbox(item) for item in self.line_nb_canvas.find_all()]
        max_width = (min(box[2] - box[0] for box in all_boxes)) * 4
        self.line_nb_canvas.configure(width=max_width + 20)
        for item in self.line_nb_canvas.find_all():
            self.line_nb_canvas.move(item, max_width, 0)

    def get_filename_from_champion_name(self) -> (str, None):
        content = self.lines
        for line in content:
            if line.startswith(".name "):
                first_quote = line.find('"')
                if first_quote == -1:
                    break
                second_quote = line.find('"', first_quote + 1)
                if second_quote == -1:
                    break
                name = line[first_quote + 1:second_quote]
                if len(name) == 0:
                    break
                return name.replace(" ", "_").lower() + ".s"
        return None

    def open(self) -> bool:
        if not os.path.isfile(self.filepath):
            showwarning("An error occurs...", f"Can't open '{self.filepath}'")
            return False
        with open(self.filepath, "r") as file:
            self.default_file_content = file.read()
            self.text_editor.insert("1.0", self.default_file_content)
            self.text_editor.edit_reset()
            self.text_editor.edit_modified(False)
        self.set_modified_status(False, on_opening=True)
        return True

    def save(self) -> bool:
        if self.new_file:
            return self.master.save_file_as()
        self.default_file_content = self.text_editor.get("1.0", "end-1c")
        with open(self.filepath, "w") as file:
            file.write(self.default_file_content)
        self.set_modified_status(False)
        self.text_editor.edit_modified(False)
        return True

    def save_as(self, filepath: str) -> bool:
        self.master.files_opened[filepath] = self.master.files_opened[self.filepath]
        self.master.files_opened.pop(self.filepath)
        self.filepath = filepath
        self.filename = get_filename(filepath)
        self.new_file = False
        return self.save()

    def close(self) -> bool:
        if self.modified:
            save_file = askyesnocancel(
                f"{self.filename} - Modifications not saved",
                "This file was modified and was not saved.\nDo you want to save this file ?"
            )
            if save_file is None:
                return False
            if save_file and not self.save():
                return False
        self.master.forget(self.id)
        self.master.files_opened.pop(self.filepath)
        return True

    def undo(self) -> None:
        try:
            self.text_editor.edit_undo()
        except tk.TclError:
            pass

    def redo(self) -> None:
        try:
            self.text_editor.edit_redo()
        except tk.TclError:
            pass

    def copy_to_clipboard(self, remove_from_editor=False) -> bool:
        try:
            txt = self.text_editor.get("sel.first", "sel.last")
            self.clipboard_clear()
            self.clipboard_append(txt)
            if remove_from_editor:
                self.text_editor.delete("sel.first", "sel.last")
        except tk.TclError:
            return False
        return True

    def paste_from_clipboard(self) -> None:
        try:
            self.text_editor.get("sel.first", "sel.last")
        except tk.TclError:
            pass
        else:
            self.text_editor.mark_set("insert", "sel.first")
            self.text_editor.delete("sel.first", "sel.last")
        self.text_editor.insert("insert", self.clipboard_get())

    def check_file_status(self) -> None:
        actual = self.text_editor.get("1.0", "end-1c")
        if self.text_editor.edit_modified():
            self.text_editor.edit_separator()
            self.text_editor.edit_modified(False)
        self.set_modified_status(actual != self.default_file_content)

    def set_modified_status(self, status: bool, on_opening=False) -> None:
        self.modified = status
        if not on_opening:
            if self.modified and not self.new_file:
                self.master.tab(self.id, text=self.filename + " - Modified")
            else:
                self.master.tab(self.id, text=self.filename)

    def add(self) -> None:
        self.master.add(self, text=self.filename)

    def select(self) -> None:
        self.master.select(self.id)
        self.text_editor.focus_set()

    def set_template(self, name: str, comment: str, author: str) -> None:
        content = [line for line in self.lines if not line.startswith(".name") and not line.startswith(".comment")]
        header = [
            "#",
            "# {name} champion for CoreWar".format(name=name),
            "#",
            "# By {author}".format(author=author),
            "#",
            "# {date}".format(date=date.today().strftime("%c")),
            "#",
            ".name \"{name}\"".format(name=name),
            ".comment \"{comment}\"".format(comment=comment)
        ]
        content = header + content
        self.text_editor.delete("1.0", "end")
        self.text_editor.insert("1.0", "\n".join(content))

    def insert_command(self, cmd: str) -> None:
        insert = self.text_editor.index(tk.INSERT).split(".")
        end_of_line = insert[0] + "." + tk.END
        self.text_editor.insert(end_of_line, "\n" + cmd)

class Editor(ttk.Notebook):
    def __init__(self, *args, **kwargs) -> None:
        ttk.Notebook.__init__(self, *args, **kwargs)
        self.files_opened = dict()
        self.last_opened_folder = os.getcwd()
        self.index_new_file = 0
        self.style = ttk.Style()
        self.style.configure('TNotebook.Tab', font=("", 12))
        if os.path.isfile(EDITOR_SAVE_FILE):
            with open(EDITOR_SAVE_FILE, "rb") as save:
                data = pickle.load(save)
            self.last_opened_folder = data["last_folder"]
            for file in data["file_list"]:
                self.open_file(file)
            if data.get("actual") and data["actual"] in self.files_opened:
                self.files_opened[data["actual"]].select()

    def close_workspace(self) -> bool:
        file_list = list()
        actual_file = None if not self.files_opened else self.get_current_tab().filepath
        for tab in list(self.files_opened.values()):
            if not tab.close():
                return False
            file_list.append(str(tab.filepath))
        data = {
            "file_list": file_list,
            "actual": actual_file,
            "last_folder": self.last_opened_folder
        }
        with open(EDITOR_SAVE_FILE, "wb") as save:
            pickle.dump(data, save)
        return True

    def create_new_file(self):
        self.index_new_file += 1
        name = "new-{0}".format(self.index_new_file)
        new_tab = EditorTab(self, name, new_file=True)
        self.files_opened[name] = new_tab
        new_tab.add()
        new_tab.select()

    def open_file(self, filepath=None) -> None:
        if filepath is None:
            filepath = askopenfilename(
                title="Open assembly file",
                initialdir=self.last_opened_folder,
                defaultextension='.s',
                filetypes=[("Assembly files", "*.s"), ("All files", "*")]
            )
            if filepath is None or len(filepath) == 0:
                return
        if not os.path.isabs(filepath):
            filepath = os.path.abspath(filepath)
        if filepath in self.files_opened:
            self.files_opened[filepath].select()
        else:
            new_tab = EditorTab(self, filepath)
            if new_tab.open():
                self.files_opened[filepath] = new_tab
                new_tab.add()
                new_tab.select()
                new_tab.update_lines()
                self.last_opened_folder = os.path.split(filepath)[0]

    def start_template(self):
        tab = self.get_current_tab()
        if tab is None:
            return
        template = Template(self.winfo_toplevel())
        self.wait_window(template)
        if not template.validated:
            return
        tab.set_template(template.name, template.comment, template.author)

    def insert_command(self, cmd: str) -> None:
        if len(cmd) == 0:
            return
        tab = self.get_current_tab()
        if tab is not None:
            tab.insert_command(cmd)

    def get_current_tab(self) -> EditorTab:
        if len(self.files_opened) > 0:
            return self.nametowidget(self.select())
        return None

    def get_file(self) -> str:
        tab = self.get_current_tab()
        if tab is None:
            return str()
        return tab.filepath

    def update_tab(self):
        tab = self.get_current_tab()
        if tab is not None:
            tab.check_file_status()
            tab.update_lines()

    def save_in_file(self) -> None:
        tab = self.get_current_tab()
        if tab is not None:
            tab.save()

    def save_all_files(self) -> None:
        for tab in list(self.files_opened.values()):
            tab.save()

    def save_file_as(self) -> bool:
        tab = self.get_current_tab()
        if tab is None:
            return False
        filepath = asksaveasfilename(
            title="Save assembly file",
            initialdir=self.last_opened_folder,
            initialfile=tab.get_filename_from_champion_name(),
            defaultextension='.s',
            filetypes=[("Assembly files", "*.s"), ("All files", "*")]
        )
        if filepath is None or len(filepath) == 0:
            return False
        return tab.save_as(filepath)

    def close_file(self) -> None:
        tab = self.get_current_tab()
        if tab is not None:
            tab.close()

    def close_all_files(self) -> None:
        for tab in list(self.files_opened.values()):
            tab.close()

    def undo_last_modification(self):
        tab = self.get_current_tab()
        if tab is not None:
            tab.undo()

    def redo_last_undo(self):
        tab = self.get_current_tab()
        if tab is not None:
            tab.redo()

    def copy_to_clipboard(self):
        tab = self.get_current_tab()
        if tab is not None:
            tab.copy_to_clipboard()

    def cut_to_clipboard(self):
        tab = self.get_current_tab()
        if tab is not None:
            tab.copy_to_clipboard(remove_from_editor=True)

    def paste_from_clipboard(self):
        tab = self.get_current_tab()
        if tab is not None:
            tab.paste_from_clipboard()