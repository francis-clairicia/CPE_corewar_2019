/*
** EPITECH PROJECT, 2020
** mnemonic sti
** File description:
** corewar
*/

#include "corewar.h"
#include "mymacros.h"

int get_thd_value_sti(champ_t *chp, battle_t *bat, int param, int *idx)
{
    int nb = 0;
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

int get_scd_value_sti(champ_t *chp, battle_t *bat, int param, int *idx)
{
    int nb = 0;
    int fst_value = 0;

    if (param == T_REG) {
        if (is_register(bat->mem[(*idx + 1) % MEM_SIZE]) == 1) {
            fst_value = chp->reg[bat->mem[(*idx + 1) % MEM_SIZE] - 1];
            *idx += 1;
        } else
            *idx = -1;
    }
    if (param == T_DIR) {
        fst_value = read_from_mem(bat, *idx + 1, IND_SIZE);
        *idx += 2;
    }
    if (param == T_IND) {
        nb = read_from_mem(bat, *idx + 1, IND_SIZE);
        fst_value = read_from_mem(bat, chp->pc + nb, IND_SIZE);
        *idx += 2;
    }
    return fst_value;
}

int mne_sti(champ_t *chp, battle_t *bat)
{
    int *param = get_param_type(bat->mem[(chp->pc + 1) % MEM_SIZE]);
    int idx = chp->pc + 1;
    int fst_param = 0;
    int scd_param = 0;
    int thd_param = 0;

    ICHECK(param);
    if (param[0] != T_REG || param[1] == 0
    || param[2] == T_IND || param[2] == 0) {
        chp->pc += 1;
        return 0;
    }
    if (is_register(bat->mem[(idx + 1) % MEM_SIZE])) {
        fst_param = chp->reg[bat->mem[(idx + 1) % MEM_SIZE] - 1];
        scd_param = get_scd_value_sti(chp, bat, param[1], idx + 2);
        thd_param = get_thd_value_sti(chp, bat, param[2], idx + 1);
        if (idx != -1)
            add_parameter(bat->mem, fst_param, 4,
            chp->pc + (scd_param + thd_param) % IDX_MOD);
    }
    chp->pc += param[0] + param[1] + param[2] + 2;
    return 0;
}