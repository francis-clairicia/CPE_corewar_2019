/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** init_ncurses.c
*/

#include "ncurses_bonus.h"

void init_ncurses(void)
{
    initscr();
    noecho();
    cbreak();
    curs_set(0);
}