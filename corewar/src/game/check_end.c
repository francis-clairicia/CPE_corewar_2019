/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** check_end.c
*/

#include "corewar.h"
#include "mymacros.h"

static bool any_child_said_live(champ_t *children)
{
    if (children == NULL)
        return (false);
    for (champ_t *child = children; child; child = child->next) {
        if (child->live)
            return (true);
        if (any_child_said_live(child->children))
            return (true);
    }
    return (false);
}

static bool check_no_live_champ(champ_t *champ, battle_t *battle)
{
    int count = 0;

    for (champ_t *tmp = champ; tmp; tmp = tmp->next) {
        if (tmp->live == false && any_child_said_live(tmp->children) == false)
            tmp->die = true;
        tmp->live = false;
        if (tmp->die == true)
            count++;
    }
    if (battle->nb_champ - count <= 0)
        return true;
    return false;
}

static void check_status(champ_t *champ)
{
    for (champ_t *tmp = champ; tmp; tmp = tmp->next) {
        if (tmp->status == 1 && tmp->die == false && tmp->op.code != 0)
            tmp->act = true;
        if (tmp->status > 0 && tmp->die == false)
            tmp->status -= 1;
        for (champ_t *child = tmp->children; child; child = child->next) {
            check_status(child);
        }
    }
}

bool no_end(battle_t *battle, champ_t *champ)
{
    if (battle->dump != -1 && battle->tot_cycle >= battle->dump) {
        print_dump(battle, champ);
        return false;
    }
    if (battle->cycle >= battle->cycle_die) {
        if (check_no_live_champ(champ, battle) == true)
            return false;
        battle->cycle = 0;
    }
    if (battle->nb_live >= NBR_LIVE) {
        battle->cycle_die -= CYCLE_DELTA;
        battle->nb_live = 0;
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