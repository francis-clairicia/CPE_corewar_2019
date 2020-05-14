# -*- coding: Utf-8 -*

import pygame
from pygame.font import Font, SysFont
from pygame.sprite import Sprite
try:
    from window import Window
except ImportError:
    from my_pygame.window import Window

class Drawable(Sprite):
    def __init__(self, surface=pygame.Surface((0, 0), flags=pygame.SRCALPHA), rotate=0, **kwargs):
        Sprite.__init__(self)
        self.__sounds = list()
        self.rect = surface.get_rect()
        self.image = surface
        self.draw_sprite = True
        self.valid_size = True
        if rotate != 0:
            self.rotate(rotate)
        self.move(**kwargs)

    def __setattr__(self, name, value):
        if isinstance(value, pygame.mixer.Sound):
            value.set_volume(float(Window.sound_volume()))
            self.__sounds.append(value)
        return object.__setattr__(self, name, value)

    def fill(self, color):
        self.image.fill(color)

    def show(self):
        self.draw_sprite = True

    def hide(self):
        self.draw_sprite = False

    def is_shown(self):
        return bool(self.draw_sprite and self.valid_size)

    @property
    def image(self):
        return self.__surface

    @image.setter
    def image(self, surface):
        x = self.rect.x if hasattr(self, "rect") else 0
        y = self.rect.y if hasattr(self, "rect") else 0
        self.__surface = surface
        self.rect = self.__surface.get_rect(x=x, y=y)

    @property
    def sounds(self):
        return self.__sounds

    def draw(self, surface):
        if self.draw_sprite:
            surface.blit(self.image, self.rect)

    def move(self, **kwargs):
        self.rect = self.image.get_rect(**kwargs)
        return self.rect

    def move_ip(self, x: float, y: float):
        self.rect.move_ip(x, y)

    def rotate(self, angle: int):
        while not 0 <= angle < 360:
            angle += 360 if angle < 0 else -360
        if angle != 0:
            self.image = pygame.transform.rotate(self.image, angle)

    def set_size(self, *args, smooth=True):
        size = args if len(args) == 2 else args[0]
        if not isinstance(size, (tuple, list)):
            size = (size, size)
        size = (round(size[0]), round(size[1]))
        if size[0] != 0 and size[1] != 0:
            if smooth:
                self.image = pygame.transform.smoothscale(self.image, size)
            else:
                self.image = pygame.transform.scale(self.image, size)
            self.valid_size = True
        else:
            self.valid_size = False

    def set_width(self, width):
        height = 0 if width == 0 else round(self.rect.h * width / self.rect.w)
        self.set_size(width, height)

    def set_height(self, height):
        width = 0 if height == 0 else round(self.rect.w * height / self.rect.h)
        self.set_size(width, height)

    left = property(lambda self: self.rect.left)
    right = property(lambda self: self.rect.right)
    top = property(lambda self: self.rect.top)
    bottom = property(lambda self: self.rect.bottom)
    x = left
    y = top
    size = property(lambda self: self.rect.size)
    width = property(lambda self: self.rect.width)
    height = property(lambda self: self.rect.height)
    w = width
    h = height
    center = property(lambda self: self.rect.center)
    centerx = property(lambda self: self.rect.centerx)
    centery = property(lambda self: self.rect.centery)
    topleft = property(lambda self: self.rect.topleft)
    topright = property(lambda self: self.rect.topright)
    bottomleft = property(lambda self: self.rect.bottomleft)
    bottomright = property(lambda self: self.rect.bottomright)
    midtop = property(lambda self: self.rect.midtop)
    midbottom = property(lambda self: self.rect.midbottom)
    midleft = property(lambda self: self.rect.midleft)
    midright = property(lambda self: self.rect.midright)

class Image(Drawable):
    def __init__(self, filepath: str, size=None, **kwargs):
        Drawable.__init__(self, pygame.image.load(filepath).convert_alpha())
        if size is not None:
            self.set_size(size)
        self.move(**kwargs)

class Text(Drawable):
    def __init__(self, text: str, font, color: tuple, **kwargs):
        if isinstance(font, (tuple, list)):
            if str(font[0]).endswith((".ttf", ".otf")):
                self.font = Font(*font)
            else:
                self.font = SysFont(*font)
        else:
            self.font = font
        self.text = str(text)
        self.color = color
        Drawable.__init__(self, self.font.render(self.text, True, self.color), **kwargs)

    def copy(self):
        copy_text = Text(self.text, self.font, self.color)
        copy_text.rect = self.rect
        return copy_text

    def get_string(self):
        return self.text

    def get_font(self):
        return self.font

    def refresh(self):
        self.image = self.font.render(self.text, True, self.color)

    def set_string(self, text: str):
        self.text = str(text)
        self.refresh()

    def set_color(self, color: tuple):
        self.color = tuple(color)
        self.refresh()

class RectangleShape(Drawable):
    def __init__(self, width: int, height: int, color: tuple, outline=0, outline_color=(0, 0, 0), **kwargs):
        Drawable.__init__(self, surface=pygame.Surface((int(width), int(height)), flags=pygame.SRCALPHA), **kwargs)
        self.color = color
        self.outline = outline
        self.outline_color = outline_color

    def draw(self, surface):
        if self.is_shown():
            self.draw_shape(surface)

    def draw_shape(self, surface):
        surface.blit(self.image, self.rect)
        if self.outline > 0:
            pygame.draw.rect(surface, self.outline_color, self.rect, self.outline)
        return self.rect

    @property
    def color(self):
        return self.__color

    @color.setter
    def color(self, value: tuple):
        self.image.fill(value)
        self.__color = value


class Button(RectangleShape):
    def __init__(self, master: Window, text: str, font=None, command=None,
                 bg=(255, 255, 255), fg=(0, 0, 0),
                 outline=2, outline_color=(0, 0, 0),
                 hover_bg=(235, 235, 235), hover_fg=None, hover_sound=None,
                 active_bg=(128, 128, 128), active_fg=None, on_click_sound=None,
                 **kwargs):
        if font is None:
            font = SysFont(pygame.font.get_default_font(), 15)
        self.text = Text(text, font, fg)
        w, h = (self.text.w + 20, self.text.h + 20)
        RectangleShape.__init__(self, w, h, bg, outline, outline_color, **kwargs)
        self.fg = fg
        self.bg = bg
        self.hover_fg = fg if hover_fg is None else hover_fg
        self.hover_bg = bg if hover_bg is None else hover_bg
        self.hover_sound = None if hover_sound is None else pygame.mixer.Sound(hover_sound)
        self.active_fg = fg if active_fg is None else active_fg
        self.active_bg = bg if active_bg is None else active_bg
        self.on_click_sound = None if on_click_sound is None else pygame.mixer.Sound(on_click_sound)
        self.callback = command
        self.active = False
        self.hover = False
        master.bind_event(pygame.MOUSEBUTTONDOWN, self.mouse_click_down)
        master.bind_event(pygame.MOUSEBUTTONUP, self.mouse_click_up)
        master.bind_mouse(self.mouse_motion)

    def draw(self, surface):
        if self.is_shown():
            self.draw_shape(surface)
            self.text.move(center=self.center)
            self.text.draw(surface)

    def mouse_click_up(self, event):
        if not self.active:
            return
        self.active = False
        self.on_click_up()
        if self.rect.collidepoint(event.pos):
            if isinstance(self.on_click_sound, pygame.mixer.Sound):
                self.on_click_sound.play()
            if self.callback is not None:
                self.callback()

    def mouse_click_down(self, event):
        if self.rect.collidepoint(event.pos):
            self.active = True
            self.on_click_down()

    def mouse_motion(self, mouse_pos):
        if self.rect.collidepoint(mouse_pos):
            if self.hover is False:
                if isinstance(self.hover_sound, pygame.mixer.Sound):
                    self.hover_sound.play()
                self.hover = True
            self.color = self.hover_bg if not self.active else self.active_bg
            self.text.set_color(self.hover_fg if not self.active else self.active_fg)
        else:
            self.color = self.bg
            self.text.set_color(self.fg)
            self.hover = False

    def on_click_down(self):
        pass

    def on_click_up(self):
        pass

class ImageButton(Button):

    def __init__(self, master: Window, image: Image, show_bg=False, **kwargs):
        Button.__init__(self, master, str(), **kwargs)
        self.image_button = image
        self.show_background(show_bg)
        size = (self.image_button.w + 20, self.image_button.h + 20)
        self.offset = [0, 0]
        self.set_size(size)

    def show_background(self, status: bool):
        self._show = bool(status)

    def draw(self, surface):
        if self.is_shown():
            if self._show:
                self.draw_shape(surface)
            self.image_button.move(center=self.center)
            self.image_button.move_ip(*self.offset)
            self.image_button.draw(surface)

    def on_click_up(self):
        if not self._show:
            self.offset[1] = 0

    def on_click_down(self):
        if not self._show:
            self.offset[1] = 3

class TextButton(Button):
    def __init__(self, master: Window, text: str, color: tuple, font, outline=0, shadow=(0, 0, 0), offset=3, **kwargs):
        kwargs["bg"] = kwargs["hover_bg"] = kwargs["active_bg"] = (0, 0, 0, 0)
        kwargs["fg"] = color
        Button.__init__(self, master, text, font=font, outline=outline, **kwargs)
        self.shadow = shadow
        self.__offset = offset
        self.offset = 0

    def draw(self, surface):
        if self.is_shown():
            self.draw_shape(surface)
            self.text.move(center=self.center)
            self.draw_shadow(surface)
            self.text.move_ip(0, self.offset)
            self.text.draw(surface)

    def draw_shadow(self, surface):
        copy_text = self.text.copy()
        copy_text.set_color(self.shadow)
        copy_text.move_ip(0, self.__offset)
        copy_text.draw(surface)

    def on_click_up(self):
        self.offset = 0

    def on_click_down(self):
        self.offset = self.__offset

class Entry(RectangleShape):
    def __init__(self, master: Window, font=None, width=10, bg=(255, 255, 255), fg=(0, 0, 0),
                 highlight_color=(128, 128, 128), **kwargs):
        self.text = Text("".join("1" for _ in range(width)), font, fg)
        size = (self.text.w + 20, self.text.h + 20)
        RectangleShape.__init__(self, size, bg, **kwargs)
        self.text.set_string("")
        self.nb_chars = width
        self.default_color = self.outline_color
        self.highlight_color = highlight_color
        self.focus = False
        master.bind_event(pygame.MOUSEBUTTONUP, self.focus_set)
        master.bind_event(pygame.KEYDOWN, self.key_press)

    def draw(self, surface):
        if self.is_shown():
            self.draw_shape(surface)
            self.text.move(left=self.left + 10, centery=self.centery)
            self.text.draw(surface)
            if self.focus:
                cursor_start = (self.text.right + 2, self.text.top)
                cursor_end = (self.text.right + 2, self.text.bottom)
                pygame.draw.line(surface, self.text.color, cursor_start, cursor_end, 2)

    def get(self):
        return self.text.get_string()

    def key_press(self, event):
        if not self.focus:
            return
        text = self.text.get_string()
        if event.key == pygame.K_BACKSPACE:
            self.text.set_string(text[:-1])
        elif len(text) < self.nb_chars:
            self.text.set_string(text + event.unicode)

    def focus_set(self, event):
        self.focus = self.rect.collidepoint(event.pos)
        self.outline_color = self.default_color if not self.focus else self.highlight_color

class Scale(RectangleShape):

    S_TOP = "top"
    S_BOTTOM = "bottom"
    S_LEFT = "left"
    S_RIGHT = "right"
    S_INSIDE = "inside"

    def __init__(self, master: Window, width: int, height: int, color: tuple, scale_color: tuple, from_=0, to=1, default=None, command=None, **kwargs):
        RectangleShape.__init__(self, width, height, (0, 0, 0, 0), **kwargs)
        if to <= from_:
            raise ValueError("end value 'to' must be greather than 'from'")
        self.__start = from_
        self.__end = to
        self.callback = command
        self.percent = 0
        if default is not None:
            self.value = default
        self.active = False
        kwargs.pop("outline", None)
        self.scale_rect = RectangleShape(width, height, scale_color, **kwargs)
        self.bg_rect = RectangleShape(width, height, color, **kwargs)
        master.bind_event(pygame.MOUSEBUTTONDOWN, self.mouse_event)
        master.bind_event(pygame.MOUSEBUTTONUP, self.mouse_event)
        master.bind_mouse(self.mouse_move_event)
        self.__show_value_params = dict()
        self.__show_label_params = dict()

    def draw(self, surface):
        self.call_update()
        if self.is_shown():
            self.scale_rect.set_size(self.width * self.percent, self.height, smooth=False)
            self.bg_rect.move(x=self.x, centery=self.centery)
            self.scale_rect.move(x=self.x, centery=self.centery)
            self.bg_rect.draw(surface)
            self.scale_rect.draw(surface)
            self.draw_shape(surface)
            if len(self.__show_value_params) > 0:
                font = self.__show_value_params["font"]
                color = self.__show_value_params["color"]
                movements = self.__show_value_params["movements"]
                round_n = self.__show_value_params["round"]
                value = round(self.value, round_n) if round_n != 0 else round(self.value)
                Text(value, font, color, **movements).draw(surface)
            if len(self.__show_label_params) > 0:
                label = self.__show_label_params["label"]
                font = self.__show_label_params["font"]
                color = self.__show_label_params["color"]
                movements = self.__show_label_params["movements"]
                Text(label, font, color, **movements).draw(surface)

    def show_value(self, font, color, side, round_n=0):
        offset = 10
        movements = {
            Scale.S_TOP: {"bottom": self.top - offset, "centerx": self.centerx},
            Scale.S_BOTTOM: {"top": self.bottom + offset, "centerx": self.centerx},
            Scale.S_LEFT: {"right": self.left - offset, "centery": self.centery},
            Scale.S_RIGHT: {"left": self.right + offset, "centery": self.centery},
            Scale.S_INSIDE: {"center": self.center}
        }
        if side not in movements:
            return
        self.__show_value_params.update(font=font, color=color, movements=movements[side], round=round_n)

    def show_label(self, label, font, color, side):
        offset = 10
        movements = {
            Scale.S_TOP: {"bottom": self.top - offset, "centerx": self.centerx},
            Scale.S_BOTTOM: {"top": self.bottom + offset, "centerx": self.centerx},
            Scale.S_LEFT: {"right": self.left - offset, "centery": self.centery},
            Scale.S_RIGHT: {"left": self.right + offset, "centery": self.centery},
        }
        if side not in movements:
            return
        self.__show_label_params.update(label=label, font=font, color=color, movements=movements[side])

    def mouse_event(self, event: pygame.event.Event):
        if event.type == pygame.MOUSEBUTTONUP:
            self.active = False
        elif self.rect.collidepoint(event.pos):
            self.active = True

    def mouse_move_event(self, mouse_pos):
        if self.active:
            self.percent = (mouse_pos[0] - self.x) / self.width

    def call_update(self):
        if hasattr(self, "callback") and self.callback is not None:
            try:
                self.callback()
            except Exception:
                pass

    @property
    def percent(self):
        return self.__percent

    @percent.setter
    def percent(self, value: float):
        if value > 1:
            value = 1
        elif value < 0:
            value = 0
        self.__percent = value
        self.__value = self.__start + (self.__percent * self.__end)

    @property
    def value(self):
        return self.__value

    @value.setter
    def value(self, value: float):
        if value > self.__end:
            value = self.__end
        elif value < self.__start:
            value = self.__start
        self.__value = value
        self.__percent = (self.__value - self.__start) / (self.__end - self.__start)