/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** launch.c
*/

#include "corewar.h"
#include "mymacros.h"

static const mnemonic_t mnemonic_list[] = {
    &mne_live,
    &mne_ld,
    &mne_st,
    &mne_add,
    &mne_sub,
    &mne_and,
    &mne_or,
    &mne_xor,
    &mne_zjmp,
    &mne_ldi,
    &mne_sti,
    &mne_fork,
    &mne_lld,
    &mne_lldi,
    &mne_lfork,
    &mne_aff
};

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

static int launch_mnemonic_without_cb(battle_t *battle, champ_t *champ)
{
    param_t params;
    int size = 0;

    my_memset(&params, 0, sizeof(params));
    size = set_param_values_without_cb(&params, battle->mem, champ->pc + 1,
        champ->op.mnemonique);
    mnemonic_list[champ->op.code - 1](&params, champ, battle);
    if (my_strcmp(champ->op.mnemonique, "zjmp") != 0)
        champ->pc += size + 1;
    return (0);
}

static int launch_mnemonic_with_cb(battle_t *battle, champ_t *champ)
{
    param_t params;
    int dir_size = 0;
    int size = 0;

    my_memset(&params, 0, sizeof(params));
    get_param_type(&params, get_coding_byte(battle->mem, champ->pc + 1));
    if (!valid_params(&params, champ->op.code)) {
        champ->pc += 1;
    } else {
        dir_size = get_dir_size(champ->op.mnemonique);
        size = set_param_values(&params, battle->mem, champ->pc + 2, dir_size);
        if (valid_values(&params))
            mnemonic_list[champ->op.code - 1](&params, champ, battle);
        champ->pc += size + 1 + 1;
    }
    return (0);
}

int launch_mnemonic(battle_t *battle, champ_t *champ)
{
    ICHECK(battle)
    ICHECK(champ)
    if (my_array_contains(no_coding_byte, champ->op.mnemonique))
        return (launch_mnemonic_without_cb(battle, champ));
    return (launch_mnemonic_with_cb(battle, champ));
}