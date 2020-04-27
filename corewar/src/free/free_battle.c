/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** free_battle.c
*/

#include "corewar.h"
#include "stdlib.h"

void free_battle(battle_t *battle)
{
    free(battle->mem);
    free(battle);
}