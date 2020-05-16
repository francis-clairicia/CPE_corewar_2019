/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** menu.c
*/

#include "ncurses_bonus.h"
#include "mymacros.h"

static void display_menu(window_t window, int chose)
{
    char *list[] = {"Play", "Select your champions", "Quit"};

    box(window.window, 0, 0);
    for (int i = 0; i < 3; i++) {
        if (i == chose)
            wattron(window.window, A_REVERSE);
        mvwprintw(window.window, i + window.y / 2 - 1,
        window.x / 2 - strlen(list[i]) / 2, list[i]);
        wattroff(window.window, A_REVERSE);
    }
}

static int menu_loop(window_t window)
{
    int key = 0;
    int chose = 0;

    while (key != 'q') {
        display_menu(window, chose);
        key = wgetch(window.window);
        if (key == KEY_UP)
            chose = (chose - 1 < 0) ? 2 : chose - 1;
        if (key == KEY_DOWN)
            chose = (chose + 1 > 2) ? 0 : chose + 1;
        if (key == 10) {
            return chose;
        }
    } return 2;
}

int menu(bonus_t *bonus)
{
    your_champs(bonus);
    window_t window = create_window();

    if (window.x == 0)
        return 84;
    bonus->scene = menu_loop(window);
    bonus->scene += 1;
    if (bonus->scene == 3)
        bonus->quit = true;
    delwin(window.window);
    return 0;
}