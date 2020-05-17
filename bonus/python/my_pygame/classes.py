# -*- coding: Utf-8 -*

from typing import Tuple, Optional, Any, Union, List, Callable
import pygame
from pygame.font import Font, SysFont
from pygame.sprite import Sprite, Group

class Drawable(Sprite):
    def __init__(self, surface: Optional[pygame.Surface] = pygame.Surface((0, 0), flags=pygame.SRCALPHA),
                 rotate: Optional[int] = 0, groups: Optional[Union[List[Group], Tuple[Group, ...]]] = tuple(), **kwargs):
        Sprite.__init__(self, *groups)
        self.__sounds = list()
        self.former_moves = dict()
        self.image = surface
        self.draw_sprite = True
        self.valid_size = True
        self.rotate(rotate)
        self.move(**kwargs)

    def __setattr__(self, name: str, value: Any):
        if isinstance(value, pygame.mixer.Sound):
            self.__sounds.append(value)
        elif issubclass(type(value), Drawable):
            self.__sounds.extend(value.sounds)
        return object.__setattr__(self, name, value)

    def fill(self, color: Union[Tuple[int, int, int], Tuple[int, int, int, int]]) -> None:
        self.image.fill(color)

    def show(self) -> None:
        self.draw_sprite = True

    def hide(self) -> None:
        self.draw_sprite = False

    def is_shown(self) -> bool:
        return bool(self.draw_sprite and self.valid_size)

    @property
    def image(self) -> pygame.Surface:
        return self.__surface

    @image.setter
    def image(self, surface: pygame.Surface) -> None:
        self.__surface = surface
        self.rect = self.__surface.get_rect()
        self.mask = pygame.mask.from_surface(self.__surface)
        self.move(**self.former_moves)

    @property
    def sounds(self) -> Tuple[pygame.mixer.Sound, ...]:
        return tuple(self.__sounds)

    def draw(self, surface: pygame.Surface) -> None:
        if self.is_shown():
            surface.blit(self.image, self.rect)

    def move(self, **kwargs) -> pygame.Rect:
        x = self.rect.x if hasattr(self, "rect") else 0
        y = self.rect.y if hasattr(self, "rect") else 0
        self.rect = self.image.get_rect(**kwargs)
        if not any(key in kwargs for key in ["x", "left", "right", "center", "centerx", "topleft", "topright", "bottomleft", "bottomright", "midleft", "midright"]):
            self.rect.x = x
        if not any(key in kwargs for key in ["y", "top", "bottom", "center", "centery", "topleft", "topright", "bottomleft", "bottomright", "midleft", "midright"]):
            self.rect.y = y
        self.former_moves = kwargs.copy()
        return self.rect

    def move_ip(self, x: float, y: float) -> None:
        self.rect.move_ip(x, y)

    def rotate(self, angle: int) -> None:
        while not 0 <= angle < 360:
            angle += 360 if angle < 0 else -360
        if angle != 0:
            self.image = pygame.transform.rotate(self.image, angle)

    def set_size(self, *args, smooth=True) -> None:
        size = args if len(args) == 2 else args[0]
        if not isinstance(size, (tuple, list)):
            size = (size, size)
        size = (round(size[0]), round(size[1]))
        if size[0] > 0 and size[1] > 0:
            if smooth:
                self.image = pygame.transform.smoothscale(self.image, size)
            else:
                self.image = pygame.transform.scale(self.image, size)
            self.valid_size = True
        else:
            self.valid_size = False

    def set_width(self, width: float, smooth=True)-> None:
        height = 0 if width == 0 else round(self.rect.h * width / self.rect.w)
        self.set_size(width, height, smooth=smooth)

    def set_height(self, height: float, smooth=True) -> None:
        width = 0 if height == 0 else round(self.rect.w * height / self.rect.h)
        self.set_size(width, height, smooth=smooth)

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
        Drawable.__init__(self, pygame.image.load(filepath).convert_alpha(), **kwargs)
        if size is not None:
            self.set_size(size)

class Text(Drawable):

    T_LEFT = "left"
    T_RIGHT = "right"
    T_CENTER = "center"

    def __init__(self, text: str, font: Union[Font, SysFont, Tuple[int, str, str]], color: tuple, justify="left", **kwargs):
        Drawable.__init__(self, **kwargs)
        if font is None:
            font = SysFont(pygame.freetype.get_default_font(), 15)
        self.color = color
        self.justify = justify
        self.font = font
        self.string = text
        self.refresh()

    @property
    def font(self) -> Font:
        return self.__font

    @font.setter
    def font(self, font: Union[Font, SysFont, Tuple[int, str, str]]) -> None:
        if isinstance(font, (tuple, list)):
            if str(font[0]).endswith((".ttf", ".otf")):
                self.__font = Font(*font)
            else:
                self.__font = SysFont(*font)
        else:
            self.__font = font
        self.refresh()

    @property
    def string(self) -> str:
        return self.__str

    @string.setter
    def string(self, string: str) -> None:
        self.__str = str(string)
        self.refresh()

    def refresh(self) -> None:
        if not hasattr(self, "string") or not hasattr(self, "font"):
            return
        render_lines = list()
        for line in self.string.splitlines():
            render = self.font.render(line, True, self.color)
            render_lines.append(render)
        if len(render_lines) > 0:
            size = (
                max(render.get_width() for render in render_lines),
                sum(render.get_height() for render in render_lines)
            )
            self.image = pygame.Surface(size, flags=pygame.SRCALPHA)
            self.image.fill((0, 0, 0, 0))
            y = 0
            justify_parameters = {
                Text.T_LEFT:    {"left": 0},
                Text.T_RIGHT:   {"right": size[0]},
                Text.T_CENTER:  {"centerx": size[0] // 2},
            }
            params = justify_parameters.get(self.justify, dict())
            for render in render_lines:
                self.image.blit(render, render.get_rect(**params, y=y))
                y += render.get_height()
        else:
            self.image = pygame.Surface((0, 0), flags=pygame.SRCALPHA)

    def set_color(self, color: tuple) -> None:
        self.color = tuple(color)
        self.refresh()

class RectangleShape(Drawable):
    def __init__(self, width: int, height: int, color: tuple, outline=0, outline_color=(0, 0, 0), **kwargs):
        Drawable.__init__(self, pygame.Surface((int(width), int(height)), flags=pygame.SRCALPHA), **kwargs)
        self.color = color
        self.outline = outline
        self.outline_color = outline_color

    def draw(self, surface: pygame.Surface) -> None:
        if self.is_shown():
            self.draw_shape(surface)

    def draw_shape(self, surface) -> None:
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
    def __init__(self, master, text: str, font=None, command: Optional[Callable[..., Any]] = None,
                 bg=(255, 255, 255), fg=(0, 0, 0),
                 outline=2, outline_color=(0, 0, 0),
                 hover_bg=(235, 235, 235), hover_fg=None, hover_sound=None,
                 active_bg=(128, 128, 128), active_fg=None, on_click_sound=None,
                 **kwargs):
        RectangleShape.__init__(self, width=1, height=1, color=bg, outline=outline, outline_color=outline_color, **kwargs)
        self.text = Text(text, font, fg, justify=Text.T_CENTER)
        self.set_size(self.text.w + 20, self.text.h + 20, smooth=False)
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

    def set_text(self, string: str) -> None:
        self.text.string = string
        w, h = (self.text.w + 20, self.text.h + 20)
        self.set_size(w, h)

    def get_text(self) -> str:
        return self.text.string

    def draw(self, surface: pygame.Surface) -> None:
        if self.is_shown():
            self.draw_shape(surface)
            self.text.move(center=self.center)
            self.text.draw(surface)

    def mouse_click_up(self, event: pygame.event.Event) -> None:
        if not self.active:
            return
        self.active = False
        self.on_click_up(event)
        if self.is_shown() and event.button == 1 and self.rect.collidepoint(event.pos):
            if isinstance(self.on_click_sound, pygame.mixer.Sound):
                self.on_click_sound.play()
            if self.callback is not None:
                self.callback()

    def mouse_click_down(self, event: pygame.event.Event) -> None:
        if self.is_shown() and event.button == 1 and self.rect.collidepoint(event.pos):
            self.active = True
            self.on_click_down(event)

    def mouse_motion(self, mouse_pos: Tuple[int, int]) -> None:
        if not self.is_shown():
            return
        if self.rect.collidepoint(mouse_pos):
            if self.hover is False:
                if isinstance(self.hover_sound, pygame.mixer.Sound):
                    self.hover_sound.play()
                self.on_hover()
                self.hover = True
            self.color = self.hover_bg if not self.active else self.active_bg
            self.text.set_color(self.hover_fg if not self.active else self.active_fg)
        else:
            self.color = self.bg
            self.text.set_color(self.fg)
            if self.hover:
                self.on_leave()
            self.hover = False

    def on_click_down(self, event: pygame.event.Event) -> None:
        pass

    def on_click_up(self, event: pygame.event.Event) -> None:
        pass

    def on_hover(self) -> None:
        pass

    def on_leave(self) -> None:
        pass

class ImageButton(Button):

    def __init__(self, master, image: Image, show_bg=False, offset=3, **kwargs):
        Button.__init__(self, master, str(), **kwargs)
        self.image_button = image
        self.show_background(show_bg)
        self.set_size(self.image_button.w + 20, self.image_button.h + 20)
        self.__offset = offset
        self.offset = 0

    def show_background(self, status: bool) -> None:
        self._show = bool(status)

    def draw(self, surface: pygame.Surface) -> None:
        if self.is_shown():
            if self._show:
                self.draw_shape(surface)
            self.image_button.move(center=self.center)
            self.image_button.move_ip(0, self.offset)
            self.image_button.draw(surface)

    def on_click_up(self, event: pygame.event.Event):
        self.offset = 0

    def on_click_down(self, event):
        self.offset = self.__offset

class TextButton(Button):
    def __init__(self, master, text: str, color: tuple, font, outline=0, shadow=(0, 0, 0), offset=3, **kwargs):
        kwargs["bg"] = kwargs["hover_bg"] = kwargs["active_bg"] = (0, 0, 0, 0)
        kwargs["fg"] = color
        Button.__init__(self, master, text, font=font, outline=outline, **kwargs)
        self.shadow = shadow
        self.__offset = offset
        self.offset = 0

    def draw(self, surface: pygame.Surface) -> None:
        if self.is_shown():
            self.draw_shape(surface)
            self.text.move(center=self.center)
            if self.offset != self.__offset:
                color = tuple(self.text.color)
                self.text.set_color(self.shadow)
                self.text.move_ip(0, self.__offset)
                self.text.draw(surface)
                self.text.set_color(color)
                self.text.move(center=self.center)
            self.text.move_ip(0, self.offset)
            self.text.draw(surface)

    def on_click_up(self, event):
        self.offset = 0

    def on_click_down(self, event):
        self.offset = self.__offset

class Entry(RectangleShape):
    def __init__(self, master, font=None, width=10, bg=(255, 255, 255), fg=(0, 0, 0),
                 highlight_color=(128, 128, 128), **kwargs):
        self.text = Text("".join("1" for _ in range(width)), font, fg)
        size = (self.text.w + 20, self.text.h + 20)
        RectangleShape.__init__(self, size, bg, **kwargs)
        self.text.string = ""
        self.nb_chars = width
        self.default_color = self.outline_color
        self.highlight_color = highlight_color
        self.hover = False
        master.bind_event(pygame.MOUSEBUTTONUP, self.focus_set)
        master.bind_event(pygame.KEYDOWN, self.key_press)

    def draw(self, surface: pygame.Surface) -> None:
        if self.is_shown():
            self.draw_shape(surface)
            self.text.move(left=self.left + 10, centery=self.centery)
            self.text.draw(surface)
            if self.hover:
                cursor_start = (self.text.right + 2, self.text.top)
                cursor_end = (self.text.right + 2, self.text.bottom)
                pygame.draw.line(surface, self.text.color, cursor_start, cursor_end, 2)

    def get(self) -> str:
        return self.text.string

    def key_press(self, event: pygame.event.Event) -> None:
        if not self.hover:
            return
        if event.key == pygame.K_BACKSPACE:
            self.text.string = self.text.string[:-1]
        elif len(self.get()) < self.nb_chars:
            self.text.string += event.unicode

    def focus_set(self, event: pygame.event.Event) -> None:
        self.hover = self.rect.collidepoint(event.pos)
        self.outline_color = self.default_color if not self.hover else self.highlight_color

class Scale(RectangleShape):

    S_TOP = "top"
    S_BOTTOM = "bottom"
    S_LEFT = "left"
    S_RIGHT = "right"
    S_INSIDE = "inside"

    def __init__(self, master, width: int, height: int, color: tuple, scale_color: tuple, from_=0, to=1, default=None, command=None, **kwargs):
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

    def draw(self, surface: pygame.Surface) -> None:
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
            Scale.S_TOP:    {"bottom": self.top - offset, "centerx": self.centerx},
            Scale.S_BOTTOM: {"top": self.bottom + offset, "centerx": self.centerx},
            Scale.S_LEFT:   {"right": self.left - offset, "centery": self.centery},
            Scale.S_RIGHT:  {"left": self.right + offset, "centery": self.centery},
            Scale.S_INSIDE: {"center": self.center}
        }
        if side not in movements:
            return
        self.__show_value_params.update(font=font, color=color, movements=movements[side], round=round_n)

    def show_label(self, label, font, color, side):
        offset = 10
        movements = {
            Scale.S_TOP:    {"bottom": self.top - offset, "centerx": self.centerx},
            Scale.S_BOTTOM: {"top": self.bottom + offset, "centerx": self.centerx},
            Scale.S_LEFT:   {"right": self.left - offset, "centery": self.centery},
            Scale.S_RIGHT:  {"left": self.right + offset, "centery": self.centery},
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