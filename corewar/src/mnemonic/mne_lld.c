/*
** EPITECH PROJECT, 2020
** mnemonic lld
** File description:
** corewar
*/

#include "corewar.h"
#include "mymacros.h"

int mne_lld(champ_t *chp, battle_t *bat)
{
    int *param = get_param_type(bat->mem[(chp->pc + 1) % MEM_SIZE]);
    int idx = chp->pc + 1;
    int fst_param = 0;
    int scd_param = 0;
    int start_to_read = 0;

    ICHECK(param);
    if (param[0] == 0 || param[0] == T_REG || param[1] == T_REG) {
        chp->pc += 1;
        return 0;
    }
    fst_param = get_two_value(bat, chp, &idx, param[0]);
    if (is_register(bat->mem[(idx + 1) % MEM_SIZE]) == 1) {
        scd_param = bat->mem[(idx + 1) % MEM_SIZE];
        start_to_read = (chp->pc + fst_param);
        chp->reg[scd_param - 1] = read_from_mem(bat, start_to_read, REG_SIZE);
        chp->carry = 1;
        chp->pc = idx + 2;
    }
    return 0;
}