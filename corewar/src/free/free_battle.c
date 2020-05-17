/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** free_battle.c
*/

#include <stdlib.h>
#include "corewar.h"

void free_battle(battle_t *battle)
{
    free(battle->mem);
    free(battle->check_mem);
    my_free_list(&battle->lines, NULL);
    my_free_list(&battle->pc_printed, NULL);
    free(battle);
}