/*
** EPITECH PROJECT, 2020
** mnemonic st
** File description:
** corewar
*/

#include "corewar.h"

int mne_st(champ_t *champ, battle_t *battle)
{
    int to_adress = 0;
    int fst_param = get_value(champ, battle);
    int scd_param = get_value(champ, battle);

    if (is_register(fst_param) == 84)
        return 84;
    if (is_register(scd_param == 1))
        champ->reg[scd_param - 1] = champ->reg[fst_param - 1];
    else {
        to_adress = champ->pc + (scd_param % IDX_MOD);
        // write_in_memory(champ->reg[fst_param - 1], to_adress, battle);
    }
    return 0;
}