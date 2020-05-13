/*
** EPITECH PROJECT, 2020
** mnemonic ld
** File description:
** corewar
*/

#include "corewar.h"
#include "mymacros.h"

int mne_ld(param_t const *param, champ_t *champ, battle_t *battle)
{
    ICHECK(param || !champ || !battle);
    champ->reg[param->value[1] - 1] = param->value[0];
    champ->carry = (champ->reg[param->value[1] - 1] == 0) ? 1 : 0;
    return 0;
}