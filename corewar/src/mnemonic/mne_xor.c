/*
** EPITECH PROJECT, 2020
** mnemonic xor
** File description:
** corewar
*/

#include "corewar.h"
#include "mymacros.h"

int mne_xor(param_t const *param, champ_t *champ, battle_t *battle)
{
    ICHECK(param || !champ || !battle);
    int idx = 2;
    int fst_param = get_three_value(battle->mem, champ->pc, param, &idx);
    int scd_param = get_three_value(battle->mem, champ->pc, param, &idx);

    champ->reg[param->value[0] - 1] = fst_param ^ scd_param;
    champ->carry = (champ->reg[param->value[2] - 1] == 0) ? 1 : 0;
    return 0;
}