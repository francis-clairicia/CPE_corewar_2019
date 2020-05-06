/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** game_loop.c
*/

#include "corewar.h"
#include "mymacros.h"

int game_loop(champ_t *champ, battle_t *battle)
{
    while (no_end(battle)) {
        my_printf("%d\n", battle->cycle);
    }
    if (battle->last_live) {
        my_printf("The player %d (%s) has won.\n", battle->last_live->nb_champ,
        battle->last_live->header->prog_name);
    }
    return 0;
}