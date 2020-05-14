/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** game_act.c
*/

#include "corewar.h"
#include "mymacros.h"

static char * const mnemonic_modified_memory[] = {
    "st",
    "sti",
    "ldi",
    "lld",
    "lldi",
    NULL
};

static void read_mnemonic(battle_t *battle, champ_t *champ)
{
    char c = '\0';

    c = battle->mem[champ->pc % MEM_SIZE];
    if (c >= 1 && c <= 16) {
        champ->op = op_tab[c - 1];
        champ->status = champ->op.nbr_cycles - 1;
    } else
        champ->pc += 1;
}

static bool draw_the_dump(champ_t *champ)
{
    return my_array_contains(mnemonic_modified_memory, champ->op.mnemonique);
}

static int launch_champion(battle_t *battle, champ_t *champ)
{
    if (champ->status != 0 || champ->die == true)
        return 0;
    if (champ->act == false) {
        read_mnemonic(battle, champ);
    } else {
        IRETURN(launch_mnemonic(battle, champ));
        champ->act = false;
        battle->draw_dump |= draw_the_dump(champ);
    }
    return (0);
}

int game_act(battle_t *battle, champ_t *champ)
{
    IRETURN(launch_champion(battle, champ));
    for (champ_t *tmp = champ->children; tmp; tmp = tmp->next) {
        IRETURN(launch_champion(battle, tmp));
    }
    return 0;
}