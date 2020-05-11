/*
** EPITECH PROJECT, 2020
** mnemonic st
** File description:
** corewar
*/

#include "corewar.h"
#include "mymacros.h"

int write_in(battle_t *bat, champ_t *chp, int nb_to_write, int param)
{
    int scd = 0;
    int write_at = 0;

    if (param == T_REG) {
        scd = bat->mem[(chp->pc + 3) % MEM_SIZE];
        if (is_register(scd) == 1)
            chp->reg[scd - 1] = nb_to_write;
        else
            return 0;
    }
    if (param == T_IND) {
        scd = read_from_mem(bat, chp->pc + 3, IND_SIZE);
        scd = (scd % MEM_SIZE < 0) ? MEM_SIZE - scd : scd;
        write_at = chp->pc + (scd % IDX_MOD);
        add_parameter(bat->mem, nb_to_write, 4, write_at);
    }
    return 0;
}

int mne_st(champ_t *chp, battle_t *bat)
{
    int *param = get_param_type(bat->mem[(chp->pc + 1) % MEM_SIZE]);
    int idx = chp->pc + 1;
    int fst_param = 0;
    int nb_to_write = 0;

    ICHECK(param);
    if (param[0] != T_REG || param[1] == 0 || param[1] == T_DIR) {
        chp->pc += 1;
        return 0;
    }
    fst_param = bat->mem[(idx + 1) % MEM_SIZE];
    if (is_register(fst_param) == 1) {
        nb_to_write = chp->reg[fst_param - 1];
        write_in(bat, chp, nb_to_write, param[1]);
    }
    move_pc(chp, param);
    return 0;
}