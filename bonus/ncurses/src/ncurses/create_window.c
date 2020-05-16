/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** create_window.c
*/

#include "ncurses_bonus.h"

window_t create_window(void)
{
    window_t window;

    window.x = 0;
    window.y = 0;
    window.window = newwin(LINES * 1 / 3, COLS * 1 / 3,
    LINES * 1 / 3, COLS * 1 / 3);
    if (!window.window)
        return window;
    refresh();
    wrefresh(window.window);
    keypad(window.window, TRUE);
    getmaxyx(window.window, window.y, window.x);
    return window;
}