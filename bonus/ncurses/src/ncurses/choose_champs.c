/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** choose_champs.c
*/

#include "ncurses_bonus.h"
#include "mymacros.h"

static void draw_champs_loop(window_t window, int chose,
                            int len, bonus_t *bonus)
{
    your_champs(bonus);
    box(window.window, 0, 0);
    for (int i = 0; i <= window.y - 3; i++) {
        if (i == chose)
            wattron(window.window, A_REVERSE);
        if (i <= window.y - 4 && i < len)
            mvwprintw(window.window, i + 1,
            window.x / 2 - strlen(bonus->champs[i]) / 2, bonus->champs[i]);
        else if (i <= window.y - 4)
            mvwprintw(window.window, i + 1, window.x / 2, " ");
        else
            mvwprintw(window.window, i + 1, window.x / 2 - 2, "Menu");
        wattroff(window.window, A_REVERSE);
    }
}

static void remove_champ(int i, int chose, bonus_t *bonus)
{
    if (bonus->args[i + 1]) {
        bonus->args[i] = bonus->args[i + 1];
        bonus->args[i + 1] = NULL;
        remove_champ(i + 1, chose, bonus);
    } else {
        bonus->args[i] = NULL;
    }
}

static int fill_args(int chose, int len, bonus_t *bonus, int menu_place)
{
    bool verif_args = false;
    int place = 0;

    if (chose >= len || chose >= menu_place)
        return 0;
    for (int i = 0; bonus->args && bonus->args[i]; i++) {
        if (strcmp(bonus->args[i], bonus->path_champs[chose]) == 0)
            verif_args = true;
    }
    if (verif_args == true) {
        for (int i = 0; bonus->args && bonus->args[i]; i++) {
            if (strcmp(bonus->args[i], bonus->path_champs[chose]) == 0)
                remove_champ(i, chose, bonus);
        }
    } else {
        for (; bonus->args && bonus->args[place]; place++);
        bonus->args[place] = bonus->path_champs[chose];
    }
    return 0;
}

static int champs_loop(window_t window, bonus_t *bonus)
{
    int key = 0;
    int chose = 0;
    int len = my_array_len(bonus->champs);

    while (key != 'q') {
        draw_champs_loop(window, chose, len, bonus);
        key = wgetch(window.window);
        if (key == KEY_UP)
            chose = (chose - 1 < 0) ? window.y - 3 : chose - 1;
        if (key == KEY_DOWN)
            chose = (chose + 1 > window.y - 3) ? 0 : chose + 1;
        if (chose == window.y - 3 && key == 10) {
            return 0;
        } else if (key == 10)
            IRETURN(fill_args(chose, len, bonus, window.y - 3));
    }
    return -1;
}

int choose_champs(bonus_t *bonus)
{
    window_t window = create_window();

    if (window.x == 0)
        return 84;
    bonus->scene = champs_loop(window, bonus);
    IRETURN(bonus->scene);
    if (bonus->scene == -1)
        bonus->quit = true;
    else
        bonus->scene = 0;
    delwin(window.window);
    return 0;
}