/*
** EPITECH PROJECT, 2020
** mnemonic sti
** File description:
** corewar
*/

#include "corewar.h"
#include "mymacros.h"

static int get_thd_value_sti(champ_t *chp, battle_t *bat, int param, int *idx)
{
    int scd_value = 0;

    if (*idx == -1)
        return scd_value;
    *idx += 1;
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

static int get_scd_value_sti(champ_t *chp, battle_t *bat, int param, int *idx)
{
    int nb = 0;
    int fst_value = 0;

    *idx += 2;
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
        nb = (nb % MEM_SIZE < 0) ? MEM_SIZE - nb : nb;
        fst_value = read_from_mem(bat, chp->pc + nb, IND_SIZE);
        *idx += 2;
    }
    return fst_value;
}

static void end_sti(battle_t *bat, champ_t *chp, int fst_param, int sum)
{
    sum = (sum % MEM_SIZE < 0) ? MEM_SIZE - sum : sum;
    add_parameter(bat->mem, fst_param, 4, chp->pc + sum % IDX_MOD);
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
    } if (is_register(bat->mem[(idx + 1) % MEM_SIZE])) {
        fst_param = chp->reg[bat->mem[(idx + 1) % MEM_SIZE] - 1];
        scd_param = get_scd_value_sti(chp, bat, param[1], &idx);
        thd_param = get_thd_value_sti(chp, bat, param[2], &idx);
        if (idx != -1)
            end_sti(bat, chp, fst_param, scd_param + thd_param);
    }
    move_pc_special(chp, param);
    return 0;
}