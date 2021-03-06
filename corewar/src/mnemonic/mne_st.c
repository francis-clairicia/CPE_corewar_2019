/*
** EPITECH PROJECT, 2020
** mnemonic st
** File description:
** corewar
*/

#include "corewar.h"
#include "mymacros.h"

void write_in(battle_t *battle, champ_t *champ, int const value[4],
                args_type_t const type)
{
    unsigned char *mem = battle->mem;
    int write_at = 0;

    if (type == T_REG) {
        champ->reg[value[1] - 1] = champ->reg[value[0] - 1];
    }
    if (type == T_IND) {
        write_at = champ->pc + (value[1] % IDX_MOD);
        add_parameter(mem, champ->reg[value[0] - 1], REG_SIZE, write_at);
        add_line(battle, write_at);
    }
}

int mne_st(param_t const *param, champ_t *champ, battle_t *battle)
{
    ICHECK(param || !champ || !battle);
    write_in(battle, champ, param->value, param->type[1]);
    return 0;
}