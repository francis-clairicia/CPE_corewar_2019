/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** free.c
*/

#include "corewar.h"

void free_all(champ_t *champ, battle_t *battle)
{
    free_champ(champ);
    free_battle(battle);
}