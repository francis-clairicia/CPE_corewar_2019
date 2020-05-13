/*
** EPITECH PROJECT, 2020
** mnemonic and
** File description:
** corewar
*/

#include "corewar.h"
#include "mymacros.h"

int normal_get_value(unsigned char *mem, champ_t *champ, param_t *param,
                            int *idx)
{
    int nb = 0;
    static int idx_param = 0;

    if (*idx == 2)
        idx_param = 0;
    if (param->type[idx_param] == T_REG) {
            nb = champ->reg[param->value[idx_param] - 1];
            *idx += 1;
    } if (param->type[idx_param] == T_DIR) {
        nb = read_from_mem(mem, champ->pc + *idx, DIR_SIZE);
        *idx += 4;
    } if (param->type[idx_param] == T_IND) {
        nb = champ->pc + (read_from_mem(mem, champ->pc + *idx, IND_SIZE)
        % IDX_MOD);
        nb = read_from_mem(mem, nb , REG_SIZE);
        *idx += 2;
    }
    idx_param += 1;
    return nb;
}

int mne_and(param_t const *param, champ_t *champ, battle_t *battle)
{
    ICHECK(param || !champ || !battle);
    int idx = 2;
    int fst_param = get_three_value(battle->mem, champ->pc, param, &idx);
    int scd_param = get_three_value(battle->mem, champ->pc, param, &idx);

    champ->reg[param->value[2] - 1] = fst_param & scd_param;
    champ->carry = (champ->reg[param->value[2] - 1] == 0) ? 1 : 0;
    return 0;
}