/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** choose_champs.c
*/

#include "ncurses_bonus.h"
#include "mymacros.h"

static void draw_champs_loop(window_t window, int chose, int len, char **champs)
{
    for (int i = 0; i <= window.y - 3; i++) {
        if (i == chose)
            wattron(window.window, A_REVERSE);
        if (i <= window.y - 4 && i < len)
            mvwprintw(window.window, i + 1,
            window.x / 2 - strlen(champs[i]) / 2, champs[i]);
        else if (i <= window.y - 4)
            mvwprintw(window.window, i + 1, window.x / 2, " ");
        else
            mvwprintw(window.window, i + 1, window.x / 2 - 2, "menu");
        wattroff(window.window, A_REVERSE);
    }
}

static int champs_loop(window_t window, char **champs)
{
    int key = 0;
    int chose = 0;
    int len = my_array_len(champs);

    while (key != 'q') {
        draw_champs_loop(window, chose, len, champs);
        key = wgetch(window.window);
        if (key == KEY_UP)
            chose = (chose - 1 < 0) ? window.y - 3 : chose - 1;
        if (key == KEY_DOWN)
            chose = (chose + 1 > window.y - 3) ? 0 : chose + 1;
        if (chose == window.y - 3 && key == 10) {
            return 0;
        }
    }
    return -1;
}

int choose_champs(bonus_t *bonus)
{
    window_t window = create_window();

    if (window.x == 0)
        return 84;
    bonus->scene = champs_loop(window, bonus->champs);
    IRETURN(bonus->scene);
    if (bonus->scene == -1)
        bonus->quit = true;
    else
        bonus->scene = 0;
    return 0;
}