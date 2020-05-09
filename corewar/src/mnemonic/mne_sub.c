/*
** EPITECH PROJECT, 2020
** mnemonic sub
** File description:
** corewar
*/

#include "corewar.h"

int mne_sub(champ_t *champ, battle_t *battle)
{
    int *param = get_param_type(battle->mem[(champ->pc + 1) % MEM_SIZE]);
    int fst_param = battle->mem[(champ->pc + 2) % MEM_SIZE];
    int scd_param = battle->mem[(champ->pc + 3) % MEM_SIZE];
    int thd_param = battle->mem[(champ->pc + 4) % MEM_SIZE];

    if (param[0] != T_REG || param[1] != T_REG || param[2] != T_REG) {
        champ->pc += 1;
        return 0;
    }
    if (is_register(fst_param) == 84 || is_register(fst_param) == 84
    || is_register(thd_param) == 84) {
        champ->pc += 5;
        return 0;
    }
    champ->reg[thd_param - 1] = champ->reg[fst_param - 1]
    - champ->reg[scd_param - 1];
    champ->carry = 1;
    champ->pc += 5;
    return 0;
}