/*
** EPITECH PROJECT, 2020
** mnemonic lkork
** File description:
** corewar
*/

#include "corewar.h"
#include "mymacros.h"

int mne_lfork(param_t const *params, champ_t *champ, battle_t *battle)
{
    int child_pc = 0;
    champ_t *tmp = NULL;

    ICHECK(params);
    ICHECK(champ);
    ICHECK(battle);
    child_pc = champ->pc + params->value[0];
    if (champ->children) {
        for (tmp = champ->children; tmp->next; tmp = tmp->next);
        ICHECK((tmp->next = get_child(champ, child_pc)));
    } else {
        ICHECK((champ->children = get_child(champ, child_pc)));
    }
    return 0;
}