/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** game_loop.c
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

static int game_act(battle_t *battle, champ_t *champ)
{
    if (champ->status != 0 || champ->die == true)
        return 0;
    if (champ->act == false) {
        read_mnemonic(battle, champ);
    } else {
        IRETURN(launch_mnemonic(champ, battle));
        champ->act = false;
        battle->draw_dump |= draw_the_dump(champ);
    }
    for (champ_t *tmp = champ->children; tmp; tmp = tmp->next) {
        IRETURN(game_act(battle, tmp));
    }
    return 0;
}

int game_loop(champ_t *champ, battle_t *battle)
{
    while (no_end(battle, champ)) {
        for (champ_t *tmp = champ; tmp; tmp = tmp->next) {
            IRETURN(game_act(battle, tmp));
        }
        if (battle->graphic == true && battle->draw_dump == true)
            print_dump(battle->mem);
        end_loop(battle);
    }
    if (battle->dump == -1 && battle->graphic == true)
        print_dump(battle->mem);
    if (battle->last_live_nb != -1) {
        my_printf("The player %d (%s) has won.\n", battle->last_live_nb,
        battle->last_live_name);
    }
    return 0;
}