/*
** EPITECH PROJECT, 2020
** mnemonic lkork
** File description:
** corewar
*/

#include "corewar.h"
#include "mymacros.h"

int mne_lfork(champ_t *champ, battle_t *battle)
{
    int param = read_from_mem(battle, champ->pc + 1, 2);
    int child_pc = champ->pc + param;
    champ_t *tmp = champ;

    if (champ->children) {
        for (tmp = champ->children; tmp->next; tmp = tmp->next);
        ICHECK((tmp->next = get_child(champ, child_pc)));
    } else {
        ICHECK((champ->children = get_child(champ, child_pc)));
    }
    champ->pc += 3;
    return 0;
}