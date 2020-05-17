/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** params.c
*/

#include "corewar.h"
#include "mymacros.h"

static char * const no_coding_byte[] = {
    "live",
    "zjmp",
    "fork",
    "lfork",
    NULL
};

static char * const two_bytes_direct_param[] = {
    "zjmp",
    "sti",
    "ldi",
    "lldi",
    "fork",
    "lfork",
    NULL
};

static int get_dir_size(char const *mnemonic)
{
    if (my_array_contains(two_bytes_direct_param, mnemonic))
        return (IND_SIZE);
    return (DIR_SIZE);
}

static bool valid_values(param_t const *params)
{
    for (int i = 0; i < MAX_ARGS_NUMBER; i += 1) {
        if (params->type[i] == T_REG && !IS_A_REGISTER(params->value[i]))
            return (false);
    }
    return (true);
}

static int fill_param_with_cb(battle_t *battle, champ_t *champ)
{
    int dir_size = 0;

    get_param_type(&(champ->params),
    get_coding_byte(battle->mem, champ->pc + 1));
    if (!valid_params(&(champ->params), champ->op.code)) {
        champ->pc += 1;
    } else {
        dir_size = get_dir_size(champ->op.mnemonique);
        champ->params.size = set_param_values(&(champ->params), battle->mem,
        champ->pc + 2, dir_size) + 1;
        if (valid_values(&(champ->params))) {
            champ->params.act = true;
        } else {
            champ->pc += 1;
        }
    }
    return (0);
}

int fill_param(battle_t *battle, champ_t *champ)
{
    ICHECK(battle)
    ICHECK(champ)
    if (my_array_contains(no_coding_byte, champ->op.mnemonique)) {
        champ->params.size = set_param_values_without_cb(&(champ->params),
        battle->mem, champ->pc + 1, champ->op.mnemonique);
        champ->params.act = true;
        return (0);
    }
    return (fill_param_with_cb(battle, champ));
}