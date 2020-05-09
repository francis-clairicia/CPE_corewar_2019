/*
** EPITECH PROJECT, 2020
** mnemonic zjmp
** File description:
** corewar
*/

#include "corewar.h"

int mne_zjmp(champ_t *champ, battle_t *battle)
{
    int param = read_from_mem(battle, champ->pc + 1, 2);

    if (champ->carry == 1) {
        champ->pc = champ->pc + (param % IDX_MOD);
    }
    return 0;
}