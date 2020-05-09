/*
** EPITECH PROJECT, 2020
** mnemonic or
** File description:
** corewar
*/

#include "corewar.h"

int mne_or(champ_t *chp, battle_t *bat)
{
    int param[4] = get_param_type(&param, bat->mem[(chp->pc + 1) % MEM_SIZE]);
    int idx = chp->pc + 1;
    int fst_param = 0;
    int scd_param = 0;
    int thd_param = 0;

    if (param[0] == 0 || param[1] == 0 || param[2] != T_REG) {
        chp->pc += 1;
        return 0;
    }
    fst_param = get_three_value(bat, chp, &idx, param[0]);
    scd_param = get_three_value(bat, chp, &idx, param[1]);
    if (idx == -1)
        chp->pc += 1;
    if (is_register(bat->mem[(idx + 1) % MEM_SIZE]) == 1 && idx != -1) {
        thd_param = bat->mem[(idx + 1) % MEM_SIZE];
        chp->reg[thd_param - 1] = fst_param | scd_param;
        chp->carry = 1;
        chp->pc = idx + 1;
    }
    return 0;
}