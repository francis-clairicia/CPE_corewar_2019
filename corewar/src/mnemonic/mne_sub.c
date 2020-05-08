/*
** EPITECH PROJECT, 2020
** mnemonic sub
** File description:
** corewar
*/

#include "corewar.h"

int mne_sub(champ_t *champ, battle_t *battle)
{
    int fst_param = battle->mem[champ->pc + 2];
    int scd_param = battle->mem[champ->pc + 3];
    int thd_param = battle->mem[champ->pc + 4];

    if (is_register(fst_param) == 84 || is_register(fst_param) == 84
    || is_register(thd_param) == 84)
        return 84;
    champ->reg[thd_param - 1] = champ->reg[fst_param - 1]
    - champ->reg[scd_param - 1];
    champ->carry = 1;
    champ->pc += 5;
    return 0;
}