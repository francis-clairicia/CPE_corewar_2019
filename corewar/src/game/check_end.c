/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** check_end.c
*/

#include "corewar.h"
#include "mymacros.h"

bool no_end(battle_t *battle, champ_t *champ)
{
    if (battle->dump != -1 && battle->cycle >= battle->dump) {
        print_dump(battle->mem);
        return false;
    }
    if (battle->cycle_die <= 0)
        return false;
    battle->nb_live += 1;
    if (battle->nb_live >= NBR_LIVE) {
        if (battle->graphic == true)
            print_dump(battle->mem);
        battle->cycle_die -= CYCLE_DELTA;
        battle->nb_live = 0;
    }
    battle->cycle += 1;
    for (champ_t *tmp = champ; tmp; tmp = tmp->next) {
        if (tmp->status == 1)
            tmp->act = true;
        if (tmp->status > 0)
            tmp->status -= 1;
    }
    return true;
}