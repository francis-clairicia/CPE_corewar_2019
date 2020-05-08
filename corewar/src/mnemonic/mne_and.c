/*
** EPITECH PROJECT, 2020
** mnemonic and
** File description:
** corewar
*/

#include "corewar.h"

int mne_and(champ_t *champ, battle_t *battle)
{
    int fst_param = get_value(champ, battle);
    int scd_param = get_value(champ, battle);
    int thd_param = get_value(champ, battle);

    if (is_register(thd_param) == 84)
        return 84;
    if (is_register(fst_param) == 1)
        fst_param = champ->reg[fst_param - 1];
    if (is_register(scd_param) == 1)
        scd_param = champ->reg[scd_param - 1];
    champ->reg[thd_param - 1] = fst_param & scd_param;
    champ->carry = 1;
    return 0;
}