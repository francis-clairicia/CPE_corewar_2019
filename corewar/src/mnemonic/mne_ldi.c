/*
** EPITECH PROJECT, 2020
** mnemonic ldi
** File description:
** corewar
*/

#include "corewar.h"
#include "mymacros.h"

static int get_value(args_type_t type,
    int value, champ_t *champ, unsigned char *mem)
{
    if (type == T_REG)
        return (champ->reg[value - 1]);
    if (type == T_DIR)
        return (value);
    return (read_from_mem(mem, champ->pc + value % IDX_MOD, IND_SIZE));
}

int mne_ldi(param_t const *params, champ_t *champ, battle_t *battle)
{
    int reg_nb = 0;
    int sum = 0;
    int idx = 0;

    ICHECK(params)
    ICHECK(champ)
    ICHECK(battle)
    sum += get_value(params->type[0], params->value[0], champ, battle->mem);
    sum += get_value(params->type[1], params->value[1], champ, battle->mem);
    reg_nb = params->value[2] - 1;
    idx = champ->pc + sum % IDX_MOD;
    champ->reg[reg_nb] = read_from_mem(battle->mem, idx, REG_SIZE);
    return 0;
}