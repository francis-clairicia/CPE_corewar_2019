/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** sort_champion.c
*/

#include "corewar.h"
#include "macro.h"

static void change_order_champ(champ_t *champ)
{
    champ_t *save = NULL;
    champ_t *save2 = NULL;
    int i = 0;

    for (champ_t *tmp = champ; tmp; tmp = tmp->next) {
        if (save && save->nb_champ > tmp->nb_champ) {
            save->next = tmp->next;
            tmp->next = save;
            if (save2)
                save2->next = tmp;
        } if (i == 1 && save->nb_champ > tmp->nb_champ)
            champ = tmp;
        else if (i == 1)
            champ = save;
        if (i > 0 && save->nb_champ < tmp->nb_champ)
            save2 = save;
        else if (i > 0)
            save2 = tmp;
        save = tmp;
        i += 1;
    }
}

static int verif_order_champ(champ_t *champ)
{
    for (champ_t *tmp = champ; tmp->next; tmp = tmp->next) {
        if (tmp->nb_champ > tmp->next->nb_champ) {
            return 0;
        }
    }
    return 1;
}

void sort_champ_list(champ_t *champ)
{
    //while (verif_order_champ(champ)) {
    //    change_order_champ(champ);
    //}
    printf("%d\n", champ->nb_champ);
}