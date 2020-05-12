# -*- coding: Utf-8 -*

import tkinter as tk
from constants import ARGS_TYPE, T_REG, T_DIR, T_IND, REG_NUMBER, DIRECT_CHAR, LABEL_CHAR, LABEL_CHARS, SEPARATOR_CHAR

def my_str_contains_only(string: str, valid: str) -> bool:
    for char in string:
        if valid.find(char) == -1:
            return False
    return True

class RegisterArgument(tk.Frame):
    def __init__(self, master, *args, **kwargs):
        tk.Frame.__init__(self, master, *args, **kwargs)
        self.register = tk.StringVar()
        self.spinbox = tk.Spinbox(self, textvariable=self.register, from_=1, to=REG_NUMBER, width=2, state="readonly", readonlybackground="white")
        self.spinbox.grid(padx=10)

    def get(self) -> str:
        return "r" + self.register.get()

    def reset(self):
        self.register.set(1)

class DirectArgument(tk.Frame):
    def __init__(self, master, *args, **kwargs):
        tk.Frame.__init__(self, master, *args, **kwargs)
        self.arg_is_label = tk.BooleanVar()
        self.rb_label_false = tk.Radiobutton(self, text="Value", value=False, variable=self.arg_is_label, command=self.on_radiobutton_click)
        self.rb_label_true = tk.Radiobutton(self, text="Label", value=True, variable=self.arg_is_label, command=self.on_radiobutton_click)
        self.entry = tk.Entry(self, width=10)
        self.entry.configure(validate="key", validatecommand=(self.register(self.validate_entry), "%P"))
        self.entry.grid(row=0, column=0, columnspan=2, padx=5, pady=5)
        self.rb_label_false.grid(row=1, column=0, padx=5, pady=5)
        self.rb_label_true.grid(row=1, column=1, padx=5, pady=5)

    def get(self) -> str:
        value = self.entry.get()
        if len(value) == 0:
            return str()
        arg = value
        if self.arg_is_label.get():
            arg = LABEL_CHAR + value
        return DIRECT_CHAR + arg

    def reset(self):
        self.entry.delete(0, tk.END)
        self.arg_is_label.set(False)

    def on_radiobutton_click(self):
        self.entry.delete(0, tk.END)

    def validate_entry(self, value: str) -> bool:
        if len(value) == 0:
            return True
        if not self.arg_is_label.get():
            if value.isdigit():
                return True
        else:
            if my_str_contains_only(value, LABEL_CHARS):
                return True
        return False

class IndirectArgument(DirectArgument):

    def get(self) -> str:
        value = self.entry.get()
        if len(value) == 0:
            return str()
        arg = value
        if self.arg_is_label.get():
            arg = LABEL_CHAR + value
        return arg

class Argument(tk.LabelFrame):
    def __init__(self, master, arg_type_possible: int, *args, **kwargs):
        tk.LabelFrame.__init__(self, master, *args, **kwargs)
        self.type = tk.IntVar()
        class_dict = {
            T_REG: RegisterArgument,
            T_DIR: DirectArgument,
            T_IND: IndirectArgument
        }
        self.table = dict()
        i = 0
        for name, arg_type in [("Register", T_REG), ("Direct", T_DIR), ("Indirect", T_IND)]:
            if (arg_type_possible & arg_type) != 0:
                rb = tk.Radiobutton(self, text=name, value=arg_type, variable=self.type, command=self.on_radiobutton_click)
                rb.grid(row=i, sticky=tk.W, padx=5, pady=5)
                self.table[arg_type] = class_dict[arg_type](self)
                i += 1
        self.former_type = min(self.table.keys())
        self.type.set(self.former_type)
        self.on_radiobutton_click()

    def get(self) -> str:
        return self.table[self.type.get()].get()

    def reset(self):
        for arg in self.table.values():
            arg.reset()

    def on_radiobutton_click(self):
        self.table[self.former_type].grid_forget()
        self.table[self.type.get()].grid(row=0, column=1, rowspan=len(self.table), padx=5, pady=5)
        self.former_type = self.type.get()

class Command(tk.LabelFrame):
    def __init__(self, master, mnemonic: str, description: str, long=False):
        tk.LabelFrame.__init__(self, master, text="[Instruction \"{0}\"]".format(mnemonic), padx=10, pady=10)
        self.mnemonic = mnemonic
        self.args_type = tuple(ARGS_TYPE[mnemonic])
        self.description = description

        self.valid_label = self.register(lambda value: my_str_contains_only(value, LABEL_CHARS))
        self.label_frame = tk.Frame(self)
        self.label_frame.grid(columnspan=3, padx=5, pady=5)
        tk.Label(self.label_frame, text="Label (Optional)").grid(row=0, column=0, padx=5, pady=5)
        self.label = tk.Entry(self.label_frame, width=10, validate="key", validatecommand=(self.valid_label, "%P"))
        self.label.grid(row=0, column=1, padx=5, pady=5)
        self.instruction = str(mnemonic)
        self.args = list()
        for i, arg_type in enumerate(self.args_type):
            arg = Argument(self, arg_type, text="Parameter " + str(i + 1))
            arg.grid(row=1 + i, column=0, columnspan=3, padx=5, pady=5)
            self.args.append(arg)
        self.long_format = tk.BooleanVar(value=False)
        if long is True:
            tk.Label(self, text="Use IDX_MOD ?").grid(row=self.nb_args + 1, column=0, padx=5, pady=5)
            tk.Radiobutton(self, text="Yes", value=False, variable=self.long_format).grid(row=self.nb_args + 1, column=1, padx=5, pady=5)
            tk.Radiobutton(self, text="No", value=True, variable=self.long_format).grid(row=self.nb_args + 1, column=2, padx=5, pady=5)

    def get(self) -> str:
        if self.long_format.get() is True:
            self.instruction = "l" + self.mnemonic
        command = self.instruction + " " + SEPARATOR_CHAR.join(arg.get() for arg in self.args)
        if len(self.label.get()) > 0:
            command = self.label.get() + ": " + command
        return command

    @property
    def nb_args(self):
        return len(self.args_type)

    def reset(self):
        self.label.delete(0, tk.END)
        for arg in self.args:
            arg.reset()

class CommandList(tk.Frame):
    def __init__(self, master, *args, **kwargs):
        tk.Frame.__init__(self, master, *args, **kwargs)
        self.commands = [
            Command(self, "live", "Say \"I'm alive\""),
            Command(self, "ld", "Load a value into a register", long=True),
            Command(self, "st", "Store the value of a register"),
            Command(self, "add", "Make an addition"),
            Command(self, "sub", "Make a subtraction"),
            Command(self, "and", "Perform an 'and' (&) binary operation"),
            Command(self, "or", "Perform an 'or' (|) binary operation"),
            Command(self, "xor", "Perform a 'xor' (^) binary operation"),
            Command(self, "zjmp", "Jump to an index", long=True),
            Command(self, "ldi", "Load a value from index into a register"),
            Command(self, "sti", "Store the value of a register at index"),
            Command(self, "fork", "Duplicate your program", long=True),
            Command(self, "aff", "Display the content of a register")
        ]
        self.choice_frame = tk.Frame(self)
        self.choice_frame.grid()
        self.choices = tk.Listbox(self.choice_frame, selectmode=tk.SINGLE, font=("", 10))
        description_list = tuple(command.mnemonic + " - " + command.description for command in self.commands)
        self.choices.insert(tk.END, *description_list)
        self.choices.configure(width=max(len(description) for description in description_list))
        self.choices.bind("<<ListboxSelect>>", lambda event: self.on_select())
        self.choices.grid(row=0, column=0, sticky=tk.NSEW)
        self.choice_scrollbar = tk.Scrollbar(self.choice_frame, orient=tk.VERTICAL, command=self.choices.yview)
        self.choices.configure(yscrollcommand=self.choice_scrollbar.set)
        self.choice_scrollbar.grid(row=0, column=1, sticky=tk.NS)
        self.button_add = tk.Button(self, text="Validate", font=("", 15))
        self.selected = None

    def reset(self):
        for command in self.commands:
            command.reset()
            command.grid_forget()
        self.button_add.grid_forget()

    def on_select(self) -> None:
        selected = self.get_selected_command()
        if selected is None:
            return
        if self.selected is not None:
            self.selected.grid_forget()
        self.selected = selected
        self.selected.grid(row=1, padx=5, pady=10)
        self.button_add.grid(row=2)

    def get_selected_command(self) -> Command:
        try:
            return self.commands[self.choices.curselection()[0]]
        except IndexError:
            pass
        return None