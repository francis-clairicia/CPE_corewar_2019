/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** play.c
*/

#include "ncurses_bonus.h"

int play(bonus_t *bonus)
{
    endwin();
    if (execv("./corewar", bonus->path_champs) == -1)
        return 84;
    exit(0);
    return 0;
}