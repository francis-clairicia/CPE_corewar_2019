/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** check_end.c
*/

#include "corewar.h"
#include "mymacros.h"

static bool check_live_champ(champ_t *champ, battle_t *battle)
{
    int count = 0;

    for (champ_t *tmp = champ; tmp; tmp = tmp->next) {
        if (tmp->live == false) {
            tmp->die = true;
        }
        tmp->live = false;
        if (tmp->die == true)
            count++;
    }
    if (battle->nb_champ - count <= 1)
        return true;
    return false;
}

static void check_status(champ_t *champ)
{
    for (champ_t *tmp = champ; tmp; tmp = tmp->next) {
        if (tmp->status == 1 && tmp->die == false)
            tmp->act = true;
        if (tmp->status > 0 && tmp->die == false)
            tmp->status -= 1;
        for (champ_t *tmpp = tmp->children; tmpp; tmpp = tmpp->next) {
            check_status(tmpp);
        }
    }
}

bool no_end(battle_t *battle, champ_t *champ)
{
    if (battle->dump != -1 && battle->cycle >= battle->dump) {
        print_dump(battle->mem);
        return false;
    }
    if (battle->cycle_die <= battle->cycle && check_live_champ(champ, battle)
    == false)
        battle->cycle = 0;
    else if (battle->cycle_die <= battle->cycle)
        return false;
    if (battle->nb_live >= NBR_LIVE) {
        battle->cycle_die -= CYCLE_DELTA;
        battle->nb_live = 0;
        if (check_live_champ(champ, battle))
            return false;
        battle->cycle = 0;
    }
    check_status(champ);
    return true;
}

void end_loop(battle_t *battle)
{
    battle->cycle += 1;
    battle->tot_cycle += 1;
    battle->draw_dump = false;
}