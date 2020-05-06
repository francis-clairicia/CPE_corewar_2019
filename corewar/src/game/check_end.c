/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** check_end.c
*/

#include "corewar.h"
#include "mymacros.h"

bool no_end(battle_t *battle)
{
    if (battle->dump != -1 && battle->cycle >= battle->dump) {
        print_dump(battle->mem);
        return false;
    }
    if (battle->cycle_die <= 0)
        return false;
    battle->nb_live += 1;                    //
    if (battle->nb_live >= NBR_LIVE) {    //
        battle->cycle_die -= CYCLE_DELTA; // mettre dans live
        battle->nb_live = 0;              //
    }                                     //
    battle->cycle += 1;
    return true;
}