/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** bonus_vm.c
*/

#include "ncurses_bonus.h"
#include "mymacros.h"

int bonus_vm(void)
{
    init_game();
    IRETURN(game_loop());
    return 0;
}