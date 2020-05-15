/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** init_game.c
*/

#include "ncurses_bonus.h"

void init_game(void)
{
    initscr();
    keypad(stdscr, TRUE);
}