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

int launch_mnemonic(battle_t *battle, champ_t *champ)
{
    add_line(battle, champ->pc);
    if (champ->params.act == true) {
        IRETURN(mnemonic_list[champ->op.code - 1](&(champ->params),
        champ, battle));
        if (my_strcmp(champ->op.mnemonique, "zjmp") != 0)
            champ->pc += champ->params.size + 1;
    }
    my_memset(&(champ->params), 0, sizeof(param_t));
    return 0;
}