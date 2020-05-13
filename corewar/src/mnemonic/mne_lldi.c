/*
** EPITECH PROJECT, 2020
** mnemonic lldi
** File description:
** corewar
*/

#include "corewar.h"
#include "mymacros.h"

static void operation_lldi(battle_t *bat, champ_t *chp, int idx, int s)
{
    chp->reg[bat->mem[(idx + 1) % MEM_SIZE] - 1]
    = read_from_mem(bat, chp->pc + s, REG_SIZE);
    chp->carry = (chp->reg[bat->mem[(idx + 1) % MEM_SIZE] - 1] == 0) ? 1 : 0;
}

int mne_lldi(champ_t *chp, battle_t *bat)
{
    int *param = get_param_type(bat->mem[(chp->pc + 1) % MEM_SIZE]);
    int idx = chp->pc + 1;
    int fst_param = 0;
    int scd_param = 0;

    ICHECK(param);
    if (param[0] == 0 || param[1] == 0
    || param[1] == T_IND || param[2] != T_REG) {
        chp->pc += 1;
        free(param);
        return 0;
    }
    fst_param = get_fst_value(chp, bat, param[0], &idx);
    scd_param = get_scd_value(chp, bat, param[1], &idx);
    if (is_register(bat->mem[(idx + 1) % MEM_SIZE]) && idx != -1) {
        operation_lldi(bat, chp, idx, fst_param + scd_param);
    }
    move_pc_special(chp, param);
    free(param);
    return 0;
}