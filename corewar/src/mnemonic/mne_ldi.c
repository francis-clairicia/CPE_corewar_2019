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
        fst_value = read_from_mem(bat, chp->pc + nb, IND_SIZE);
        *idx += 2;
    }
    return fst_value;
}

static void operation_ldi(battle_t *bat, champ_t *chp, int idx, int s)
{
    chp->reg[bat->mem[(idx + 1) % MEM_SIZE] - 1]
    = read_from_mem(bat, chp->pc + (s % IDX_MOD), REG_SIZE);
    chp->carry = (chp->reg[bat->mem[(idx + 1) % MEM_SIZE] - 1] == 0) ? 1 : 0;
}

int mne_ldi(param_t const *param, champ_t *champ, battle_t *battle)
{
    ICHECK(param || !champ || !battle);
    fst_param = get_fst_value(chp, bat, param[0], &idx);
    scd_param = get_scd_value(chp, bat, param[1], &idx);
    if (is_register(bat->mem[(idx + 1) % MEM_SIZE]) && idx != -1) {
        operation_ldi(bat, chp, idx, fst_param % IDX_MOD + scd_param);
    }
    move_pc_special(chp, param);
    free(param);
    return 0;
}