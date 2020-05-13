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

int launch_mnemonic(battle_t *battle, champ_t *champ)
{
    int dir_size = 0;
    int size = 0;
    param_t params;

    ICHECK(battle)
    ICHECK(champ)
    my_memset(&params, 0, sizeof(params));
    get_param_type(&params, get_coding_byte(battle->mem, champ->pc));
    if (!valid_params(&params, champ->op.code)) {
        champ->pc += 1;
    } else {
        dir_size = get_dir_size(champ->op.mnemonique);
        size = set_param_values(&params, battle->mem, champ->pc, dir_size);
        if (valid_values(&params))
            mnemonic_list[champ->op.code - 1](&params, champ, battle);
        champ->pc += size;
    }
    return (0);
}