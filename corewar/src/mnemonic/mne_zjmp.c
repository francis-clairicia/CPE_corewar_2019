/*
** EPITECH PROJECT, 2020
** mnemonic zjmp
** File description:
** corewar
*/

#include "corewar.h"
#include "my.h"

int mne_zjmp(param_t const *params, champ_t *champ, battle_t *battle UNUSED)
{
    if (champ->carry == 1) {
        champ->pc = champ->pc + (params->value[0] % IDX_MOD);
    } else {
        champ->pc += 3;
    }
    return 0;
}