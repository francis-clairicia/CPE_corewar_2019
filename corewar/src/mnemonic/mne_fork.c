/*
** EPITECH PROJECT, 2020
** mnemonic fork
** File description:
** corewar
*/

#include "corewar.h"
#include "mymacros.h"

champ_t *get_child(champ_t *champ, int child_pc)
{
    champ_t *child = PMALLOC(child, sizeof(champ_t));

    my_memset(child, 0, sizeof(champ_t));
    child->header = champ->header;
    child->nb_champ = champ->nb_champ;
    child->pc = child_pc;
    child->carry = champ->carry;
    for (int i = 0; i < REG_NUMBER; i++)
        child->reg[i] = champ->reg[i];
    return child;
}

int mne_fork(champ_t *champ, battle_t *battle)
{
    int param = read_from_mem(battle, champ->pc + 1, 2);
    int child_pc = champ->pc + (param % IDX_MOD);
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