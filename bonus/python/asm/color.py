# -*- coding: Utf-8 -*

class Color:
    def __init__(self, red, green, blue):
        self.__red = red
        self.__green = green
        self.__blue = blue
        self.__hue = 0
        self.__saturation = 0
        self.__value = 0
        self.red = red
        self.green = green
        self.blue = blue

    @classmethod
    def from_hsv(cls, h, s, v):
        color = cls(0, 0, 0)
        color.h = h
        color.s = s
        color.v = v
        return color

    @classmethod
    def from_hex(cls, hex_code):
        if not isinstance(hex_code, str):
            raise TypeError("hex_code must be a str")
        if hex_code[0] != "#":
            raise ValueError("hex_code must start with a '#' character")
        hex_code = hex_code[1:]
        if len(hex_code) != 6:
            raise ValueError("hex_code must be formatted by #RRGGBB")
        r = int(hex_code[0:2], 16)
        g = int(hex_code[2:4], 16)
        b = int(hex_code[4:6], 16)
        return cls(r, g, b)

    def __repr__(self):
        return f"Color: red={self.red}, green={self.green}, blue={self.blue}"

    def __str__(self):
        return repr(self)

    @property
    def red(self):
        return self.__red

    @red.setter
    def red(self, value):
        if (0 <= int(value) <= 255) is False:
            raise ValueError("Color must be in range [0, 255]")
        self.__red = int(value)
        self._calculate_hsv_from_rgb()

    @property
    def green(self):
        return self.__green

    @green.setter
    def green(self, value):
        if (0 <= int(value) <= 255) is False:
            raise ValueError("Color must be in range [0, 255]")
        self.__green = int(value)
        self._calculate_hsv_from_rgb()

    @property
    def blue(self):
        return self.__blue

    @blue.setter
    def blue(self, value):
        if (0 <= int(value) <= 255) is False:
            raise ValueError("Color must be in range [0, 255]")
        self.__blue = int(value)
        self._calculate_hsv_from_rgb()

    @property
    def h(self):
        return self.__hue

    @h.setter
    def h(self, value):
        while value < 0:
            value += 360
        while value >= 360:
            value -= 360
        self.__hue = value
        self._calculate_rgb_from_hsv()

    @property
    def s(self):
        return self.__saturation

    @s.setter
    def s(self, value):
        if value < 0:
            value = 0
        elif value > 100:
            value = 100
        self.__saturation = value
        self._calculate_rgb_from_hsv()

    @property
    def v(self):
        return self.__value

    @v.setter
    def v(self, value):
        if value < 0:
            value = 0
        elif value > 100:
            value = 100
        self.__value = value
        self._calculate_rgb_from_hsv()

    @property
    def hex(self):
        value = "#"
        for color in (self.red, self.green, self.blue):
            value += "{0:0>2X}".format(color)
        return value

    def _calculate_hsv_from_rgb(self):
        r = self.red / 255
        g = self.green / 255
        b = self.blue / 255
        c_max = max((r, g, b))
        c_min = min((r, g, b))
        delta = c_max - c_min
        hue = {
            r: 0 if delta == 0 else 60 * (((g - b) / delta) % 6),
            g: 0 if delta == 0 else 60 * (((b - r) / delta) + 2),
            b: 0 if delta == 0 else 60 * (((r - g) / delta) + 4)
        }
        self.__hue = round(hue[c_max])
        self.__saturation = 0 if c_max == 0 else round(100 * delta / c_max)
        self.__value = round(100 * c_max)

    def _calculate_rgb_from_hsv(self):
        h = self.h
        s = self.s / 100
        v = self.v / 100
        c = v * s
        x = c * (1 - abs((h / 60) % 2 - 1))
        m = v - c
        hue_colors = {
            (0, 60): (c, x, 0),
            (60, 120): (x, c, 0),
            (120, 180): (0, c, x),
            (180, 240): (0, x, c),
            (240, 300): (x, 0, c),
            (300, 360): (c, 0, x)
        }
        r = 0
        g = 0
        b = 0
        for interval, hue in hue_colors.items():
            v_min, v_max = interval
            if v_min <= h < v_max:
                r, g, b = hue
                break
        self.__red = round((r + m) * 255)
        self.__green = round((g + m) * 255)
        self.__blue = round((b + m) * 255)