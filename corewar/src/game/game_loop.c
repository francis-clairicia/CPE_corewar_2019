/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** game_loop.c
*/

#include "corewar.h"
#include "mymacros.h"

static const mnemonic_t mnemonic_list[] =
{
    {&mne_live},
    {&mne_ld},
    {&mne_st},
    {&mne_add},
    {&mne_sub},
    {&mne_and},
    {&mne_or},
    {&mne_xor},
    {&mne_zjmp},
    {&mne_ldi},
    {&mne_sti},
    {&mne_fork},
    {&mne_lld},
    {&mne_lldi},
    {&mne_lfork},
    {&mne_aff}
};

static int game_act(battle_t *battle, champ_t *champ)
{
    char c = '\0';

    if (champ->status != 0)
        return 0;
    if (champ->act == false) {
        c = battle->mem[champ->pc % MEM_SIZE];
        if (c >= 1 && c <= 16) {
            champ->op = op_tab[c - 1];
            champ->status = champ->op.nbr_cycles;
        } else
            champ->pc += 1;
    } else {
        //IRETURN(mnemonic_list[c - 1].mnemonic(champ, battle));
        champ->act = false;
    }
    return 0;
}

int game_loop(champ_t *champ, battle_t *battle)
{
    while (no_end(battle, champ)) {
        for (champ_t *tmp = champ; tmp; tmp = tmp->next) {
            IRETURN(game_act(battle, tmp));
        }
    }
    if (battle->dump == -1 && battle->graphic == true)
        print_dump(battle->mem);
    if (battle->last_live) {
        my_printf("The player %d (%s) has won.\n", battle->last_live->nb_champ,
        battle->last_live->header->prog_name);
    }
    return 0;
}