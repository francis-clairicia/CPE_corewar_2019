/*
** EPITECH PROJECT, 2020
** mnemonic ldi
** File description:
** corewar
*/

#include "corewar.h"
#include "mymacros.h"

int get_scd_value(champ_t *chp, battle_t *bat, int param, int *idx)
{
    int scd_value = 0;

    if (*idx == -1)
        return scd_value;
    if (param == T_REG) {
        if (is_register(bat->mem[(*idx + 1) % MEM_SIZE]) == 1) {
            scd_value = chp->reg[bat->mem[(*idx + 1) % MEM_SIZE] - 1];
            *idx += 1;
        } else
            *idx = -1;
    }
    if (param == T_DIR) {
        scd_value = read_from_mem(bat, *idx + 1, IND_SIZE);
        *idx += 2;
    }
    return scd_value;
}

int get_fst_value(champ_t *chp, battle_t *bat, int param, int *idx)
{
    int nb = 0;
    int fst_value = 0;

    if (param == T_REG) {
        if (is_register(bat->mem[(*idx + 1) % MEM_SIZE]) == 1) {
            fst_value = chp->reg[bat->mem[(*idx + 1) % MEM_SIZE] - 1];
            *idx += 1;
        } else
            *idx = -1;
    } if (param == T_DIR) {
        fst_value = read_from_mem(bat, *idx + 1, IND_SIZE);
        *idx += 2;
    } if (param == T_IND) {
        nb = read_from_mem(bat, *idx + 1, IND_SIZE);
        nb = (nb < 0) ? MEM_SIZE - nb : nb;
        fst_value = read_from_mem(bat, chp->pc + nb, IND_SIZE);
        *idx += 2;
    }
    return fst_value;
}

int mne_ldi(champ_t *chp, battle_t *bat)
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
        s = fst_param % IDX_MOD + scd_param;
        s = (s % MEM_SIZE < 0) ? MEM_SIZE - s : s;
        chp->reg[bat->mem[(idx + 1) % MEM_SIZE] - 1]
        = read_from_mem(bat, chp->pc + (s % IDX_MOD), REG_SIZE);
        chp->carry = (chp->carry == 0) ? 1 : 0;
    } chp->pc += param[0] + param[1] + param[2] + 2;
    return 0;
}