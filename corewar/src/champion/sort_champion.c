/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** sort_champion.c
*/

#include "corewar.h"
#include "mymacros.h"

static void change_order_champ_two(champ_t **save, champ_t **save_two,
                                    champ_t **tmp)
{
    if ((*save) && (*save)->nb_champ > (*tmp)->nb_champ) {
        (*save)->next = (*tmp)->next;
        (*tmp)->next = (*save);
        if ((*save_two))
            (*save_two)->next = (*tmp);
    }
}

static void change_order_champ(champ_t **champ)
{
    champ_t *save = NULL;
    champ_t *save_two = NULL;
    int i = 0;

    for (champ_t *tmp = *champ; tmp; tmp = tmp->next, i++) {
        change_order_champ_two(&save, &save_two, &tmp);
        if (i == 1 && save->nb_champ > tmp->nb_champ)
            *champ = tmp;
        else if (i == 1)
            *champ = save;
        if (i > 0 && save->nb_champ < tmp->nb_champ)
            save_two = save;
        else if (i > 0)
            save_two = tmp;
        save = tmp;
    }
}

static int verif_order_champ(champ_t *champ)
{
    for (champ_t *tmp = champ; tmp->next; tmp = tmp->next) {
        if (tmp->nb_champ > tmp->next->nb_champ) {
            return 1;
        }
    }
    return 0;
}

void sort_champ_list(champ_t **champ)
{
    while (verif_order_champ(*champ)) {
        change_order_champ(champ);
    }
}