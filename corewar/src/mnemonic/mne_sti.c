/*
** EPITECH PROJECT, 2020
** mnemonic sti
** File description:
** corewar
*/

#include "corewar.h"
#include "mymacros.h"

static int get_index(args_type_t type, int value,
                    champ_t *champ, unsigned char *mem)
{
    int index = 0;

    if (type == T_REG)
        index = champ->reg[value - 1];
    if (type == T_DIR)
        index = value;
    if (type == T_IND)
        index = read_from_mem(mem, champ->pc + (value % IDX_MOD), IND_SIZE);
    return (index);
}

int mne_sti(param_t const *params, champ_t *champ, battle_t *battle)
{
    int register_value = 0;
    int first = 0;
    int second = 0;
    int idx = 0;

    ICHECK(params)
    ICHECK(champ)
    ICHECK(battle)
    register_value = champ->reg[params->value[0] - 1];
    first = get_index(params->type[1], params->value[1], champ, battle->mem);
    second = get_index(params->type[2], params->value[2], champ, battle->mem);
    idx = champ->pc + ((first + second) % IDX_MOD);
    add_parameter(battle->mem, register_value, REG_SIZE, idx);
    return 0;
}