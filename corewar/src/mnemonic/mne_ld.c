/*
** EPITECH PROJECT, 2020
** mnemonic ld
** File description:
** corewar
*/

#include "corewar.h"
#include "mymacros.h"

static int load_value(unsigned char *mem, int const pc, int const value,
                    args_type_t const type)
{
    int start_to_read = 0;
    int nb = 0;

    if (type == T_DIR) {
        nb = value;
    }
    if (type == T_IND) {
        start_to_read = pc + (value % IDX_MOD);
        nb = read_from_mem(mem, start_to_read , REG_SIZE);
    }
    return nb;
}

int mne_ld(param_t const *param, champ_t *champ, battle_t *battle)
{
    int reg_nb = 0;

    ICHECK(param || !champ || !battle);
    reg_nb = param->value[1] - 1;
    champ->reg[reg_nb] = load_value(battle->mem, champ->pc,
                                    param->value[0], param->type[0]);
    champ->carry = (champ->reg[reg_nb] == 0);
    return 0;
}