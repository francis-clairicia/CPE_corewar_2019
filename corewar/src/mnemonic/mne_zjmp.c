/*
** EPITECH PROJECT, 2020
** mnemonic zjmp
** File description:
** corewar
*/

#include "corewar.h"

int mne_zjmp(champ_t *champ, battle_t *battle)
{
    int param = get_value(champ, battle);

    if (champ->pc == 1) {
        champ->pc = champ->pc + (param % IDX_MOD);
    }
    return 0;
}