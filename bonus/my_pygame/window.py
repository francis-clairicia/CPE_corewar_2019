# -*- coding: Utf-8 -*

import sys
import time
import pygame

class Window:

    all_opened = list()
    __sound_volume = 0.5
    __music_volume = 0.5

    def __init__(self, size=(1920, 1080), flags=0, fps=30, bg_color=(0, 0, 0), bg_music=None):
        if not pygame.get_init():
            pygame.mixer.pre_init(44100, -16, 2, 512)
            status = pygame.init()
            if status[1] > 0:
                sys.exit(84)
        self.window = pygame.display.get_surface()
        self.main_window = False
        if self.window is None:
            self.window = pygame.display.set_mode(tuple(size), flags)
            self.main_window = True
        self.window_rect = self.window.get_rect()
        self.main_clock = pygame.time.Clock()
        self.loop = False
        self.objects = list()
        self.event_handler_dict = dict()
        self.key_handler_dict = dict()
        self.mouse_handler_list = list()
        self.fps = fps
        self.bg_color = bg_color
        self.time_after = -1
        self.time_start = 0
        self.callback_after = None
        self.bind_key(pygame.K_ESCAPE, lambda key: self.stop())
        self.bind_key(pygame.K_q, lambda key: self.stop())
        Window.all_opened.append(self)
        self.bg_music = bg_music

    def __setattr__(self, name, obj):
        if hasattr(obj, "draw"):
            if hasattr(self, name):
                delattr(self, name)
            self.add(obj)
        return object.__setattr__(self, name, obj)

    def __delattr__(self, name):
        obj = getattr(self, name)
        self.remove(obj)
        return object.__delattr__(self, name)

    def add(self, obj):
        self.objects.append(obj)

    def remove(self, obj):
        try:
            self.objects.remove(obj)
        except ValueError:
            return

    @property
    def end_list(self):
        return len(self.objects)

    def set_object_priority(self, obj, new_pos, relative_to=None):
        former_pos = self.objects.index(obj)
        del self.objects[former_pos]
        if relative_to is not None:
            new_pos += self.objects.index(relative_to)
        self.objects.insert(new_pos, obj)

    @staticmethod
    def set_icon(icon_filepath):
        icon = pygame.image.load(icon_filepath).convert_alpha()
        pygame.display.set_icon(icon)

    @staticmethod
    def set_title(title: str):
        pygame.display.set_caption(title)

    def mainloop(self, fill_bg=True):
        self.loop = True
        if self.time_after >= 0:
            self.time_start = time.time()
        if self.bg_music is not None:
            self.play_music(self.bg_music)
        while self.loop:
            self.main_clock.tick(self.fps)
            self.draw_screen(fill_bg)
            self.refresh()
            self.event_handler()
            self.check_sound_status()

    def stop(self, force=False):
        self.on_quit()
        self.loop = False
        if self.bg_music is not None:
            self.stop_music()
        if self.main_window or force:
            pygame.quit()
            sys.exit(0)

    def on_quit(self):
        pass

    def check_sound_status(self):
        if self.bg_music is None:
            return
        if not pygame.mixer.music.get_busy():
            self.play_music(self.bg_music)

    @staticmethod
    def stop_music():
        pygame.mixer.music.stop()
        pygame.mixer.music.unload()

    @staticmethod
    def play_music(filepath: str):
        Window.stop_music()
        pygame.mixer.music.load(filepath)
        pygame.mixer.music.play(-1)

    def draw_screen(self, fill=True):
        if fill:
            self.window.fill(self.bg_color)
        for obj in self.objects:
            obj.draw(self.window)

    @staticmethod
    def refresh():
        pygame.display.flip()

    def event_handler(self):
        self.mouse_handler()
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                self.stop(force=True)
            if event.type == pygame.KEYDOWN:
                self.key_handler(event.key)
            event_list = self.event_handler_dict.get(event.type, list())
            for callback in event_list:
                callback(event)
        if self.time_after < 0:
            return
        if time.time() - self.time_start >= (self.time_after / 1000):
            self.time_after = -1
            self.callback_after()

    def mouse_handler(self):
        for callback in self.mouse_handler_list:
            callback(pygame.mouse.get_pos())

    def key_handler(self, key_value):
        key_list = self.key_handler_dict.get(key_value, list())
        for callback in key_list:
            callback(key_value)

    def after(self, milliseconds: float, callback):
        self.time_after = milliseconds
        self.time_start = time.time()
        self.callback_after = callback

    def bind_event(self, event_type, callback):
        event_list = self.event_handler_dict.get(event_type)
        if event_list is None:
            event_list = self.event_handler_dict[event_type] = list()
        event_list.append(callback)

    def bind_mouse(self, callback):
        self.mouse_handler_list.append(callback)

    def bind_key(self, key_value, callback):
        key_list = self.key_handler_dict.get(key_value)
        if key_list is None:
            key_list = self.key_handler_dict[key_value] = list()
        key_list.append(callback)

    @staticmethod
    def sound_volume():
        return Window.__sound_volume

    @staticmethod
    def set_sound_volume(value: float):
        Window.__sound_volume += value
        if Window.__sound_volume > 1:
            Window.__sound_volume = 1
        elif Window.__sound_volume < 0:
            Window.__sound_volume = 0
        for window in Window.all_opened:
            for obj in window.objects:
                for sound in obj.sounds:
                    sound.set_volume(Window.__sound_volume)

    left = property(lambda self: self.window_rect.left)
    right = property(lambda self: self.window_rect.right)
    top = property(lambda self: self.window_rect.top)
    bottom = property(lambda self: self.window_rect.bottom)
    x = left
    y = top
    size = property(lambda self: self.window_rect.size)
    width = property(lambda self: self.window_rect.width)
    height = property(lambda self: self.window_rect.height)
    w = width
    h = height
    center = property(lambda self: self.window_rect.center)
    centerx = property(lambda self: self.window_rect.centerx)
    centery = property(lambda self: self.window_rect.centery)
    topleft = property(lambda self: self.window_rect.topleft)
    topright = property(lambda self: self.window_rect.topright)
    bottomleft = property(lambda self: self.window_rect.bottomleft)
    bottomright = property(lambda self: self.window_rect.bottomright)
    midtop = property(lambda self: self.window_rect.midtop)
    midbottom = property(lambda self: self.window_rect.midbottom)
    midleft = property(lambda self: self.window_rect.midleft)
    midright = property(lambda self: self.window_rect.midright)