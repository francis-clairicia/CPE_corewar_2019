/*
** EPITECH PROJECT, 2020
** add mnemonic
** File description:
** corewar
*/

#include "corewar.h"

int mne_add(champ_t *champ, battle_t *battle)
{
    int fst_param = get_value(champ, battle);
    int scd_param = get_value(champ, battle);
    int thd_param = get_value(champ, battle);

    if (is_register(fst_param) == 84 || is_register(fst_param) == 84
    || is_register(thd_param) == 84)
        return 84;
    champ->reg[thd_param - 1] = champ->reg[fst_param - 1]
    + champ->reg[scd_param - 1];
    champ->carry = 1;
    return (0);
}