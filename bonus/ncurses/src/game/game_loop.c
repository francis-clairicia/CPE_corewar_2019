/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** game_loop.c
*/

#include "ncurses_bonus.h"

int game_loop(void)
{
    int key = 0;

    while (key != 'q') {
        key = getch();
        clear();
        refresh();
    }
    endwin();
    return 0;
}