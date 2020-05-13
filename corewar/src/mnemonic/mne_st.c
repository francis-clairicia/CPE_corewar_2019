/*
** EPITECH PROJECT, 2020
** mnemonic st
** File description:
** corewar
*/

#include "corewar.h"
#include "mymacros.h"

void write_in(unsigned char *mem, champ_t *champ, int const value[4],
                args_type_t const type)
{
    int write_at = 0;

    if (type == T_REG) {
        champ->reg[value[1] - 1] = champ->reg[value[0] - 1];        
    }
    if (type == T_IND) {
        write_at = champ->pc + (read_from_mem(mem, champ->pc + 3, IND_SIZE)
        % IDX_MOD);
        add_parameter(mem, value[0], REG_SIZE, write_at);
    }
}

int mne_st(param_t const *param, champ_t *champ, battle_t *battle)
{
    ICHECK(param || !champ || !battle);

    write_in(battle->mem, champ, param->value, param->type[1]);
    return 0;
}