/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** play.c
*/

#include "ncurses_bonus.h"
#include "my.h"

int play(bonus_t *bonus)
{
    endwin();
    if (execv("./corewar", bonus->args) == -1)
        return 84;
    my_free_array(bonus->champs);
    my_free_array(bonus->path_champs);
    free(bonus);
    exit(0);
    return 0;
}