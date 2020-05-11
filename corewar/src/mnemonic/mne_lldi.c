/*
** EPITECH PROJECT, 2020
** mnemonic lldi
** File description:
** corewar
*/

#include "corewar.h"
#include "mymacros.h"

int mne_lldi(champ_t *chp, battle_t *bat)
{
    int *param = get_param_type(bat->mem[(chp->pc + 1) % MEM_SIZE]);
    int idx = chp->pc + 1;
    int fst_param = 0;
    int scd_param = 0;
    int s = 0;

    ICHECK(param);
    if (param[0] == 0 || param[1] == 0
    || param[1] == T_IND || param[2] != T_REG) {
        chp->pc += 1;
        return 0;
    } fst_param = get_fst_value(chp, bat, param[0], &idx);
    scd_param = get_scd_value(chp, bat, param[1], &idx);
    if (is_register(bat->mem[(idx + 1) % MEM_SIZE]) && idx != -1) {
        s = fst_param + scd_param;
        s = (s % MEM_SIZE < 0) ? MEM_SIZE - s : s;
        chp->reg[bat->mem[(idx + 1) % MEM_SIZE] - 1]
        = read_from_mem(bat, chp->pc + s, REG_SIZE);
        chp->carry = (chp->carry == 0) ? 1 : 0;
    } move_pc_special(chp, param);
    return 0;
}