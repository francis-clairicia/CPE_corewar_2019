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

    child_pc = (child_pc % MEM_SIZE < 0) ? (MEM_SIZE - child_pc) % MEM_SIZE :
    child_pc % MEM_SIZE;
    if (champ->childs) {
        for (tmp = champ->childs; tmp->next; tmp = tmp->next);
        ICHECK((tmp->next = get_child(champ, child_pc)));
    } else {
        ICHECK((champ->childs = get_child(champ, child_pc)));
    }
    champ->pc += 3;
    return 0;
}