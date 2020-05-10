/*
** EPITECH PROJECT, 2020
** mnemonic ld
** File description:
** corewar
*/

#include "corewar.h"
#include "mymacros.h"

int get_two_value(battle_t *battle, champ_t *champ, int *idx, int param)
{
    int fst_param = 0;
    int start_to_read = 0;
    int nb = 0;

    if (param == T_DIR) {
        nb = read_from_mem(battle, *idx + 1, REG_SIZE);
        *idx += 4;
    }
    if (param == T_IND) {
        fst_param = read_from_mem(battle, *idx + 1, IND_SIZE);
        start_to_read = (champ->pc + fst_param) % IDX_MOD;
        nb = read_from_mem(battle, start_to_read, REG_SIZE);
        *idx += 2;
    }
    return nb;
}

int mne_ld(champ_t *chp, battle_t *bat)
{
    int *param = get_param_type(bat->mem[(chp->pc + 1) % MEM_SIZE]);
    int idx = chp->pc + 1;
    int fst_param = 0;
    int scd_param = 0;
    int start_to_read = 0;

    ICHECK(param);
    if (param[0] == 0 || param[0] == T_REG || param[1] != T_REG) {
        chp->pc += 1;
        return 0;
    }
    fst_param = get_two_value(bat, chp, &idx, param[0]);
    if (is_register(bat->mem[(idx + 1) % MEM_SIZE]) == 1) {
        scd_param = bat->mem[(idx + 1) % MEM_SIZE];
        chp->reg[scd_param - 1] = fst_param;
        chp->carry = (chp->carry == 0) ? 1 : 0;
        chp->pc = idx + 2;
    }
    return 0;
}