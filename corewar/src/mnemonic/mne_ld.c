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
        nb = read_from_mem(mem, pc + 2, DIR_SIZE);
    }
    if (type == T_IND) {
        start_to_read = pc + (read_from_mem(mem, pc + 2, IND_SIZE) % IDX_MOD);
        nb = read_from_mem(mem, start_to_read , REG_SIZE);
    }
    return nb;
}

int mne_ld(param_t const *param, champ_t *champ, battle_t *battle)
{
    ICHECK(param || !champ || !battle);

    champ->reg[param->value[1] - 1] = load_value(battle->mem, champ->pc,
    param->value[0], param->type[0]);
    champ->carry = (champ->reg[param->value[1] - 1] == 0) ? 1 : 0;
    return 0;
}