/*
** EPITECH PROJECT, 2020
** add mnemonic
** File description:
** corewar
*/

#include "corewar.h"
#include "mymacros.h"

int mne_add(param_t const *param, champ_t *champ, battle_t *battle)
{
    ICHECK(param || !champ || !battle);

    champ->reg[param->value[2] - 1] = champ->reg[param->value[0] - 1]
    + champ->reg[param->value[1] - 1];
    champ->carry = (champ->reg[param->value[2] - 1] == 0) ? 1 : 0;
    return 0;
}