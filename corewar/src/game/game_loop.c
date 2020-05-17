/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** game_loop.c
*/

#include "corewar.h"
#include "mymacros.h"

int game_loop(champ_t *champ, battle_t *battle)
{
    if (battle->graphic == true)
        print_dump(battle, champ);
    while (no_end(battle, champ)) {
        for (champ_t *tmp = champ; tmp; tmp = tmp->next) {
            IRETURN(game_act(battle, tmp));
        }
        if (battle->graphic == true)
            print_dump_graphic(battle, champ);
        end_loop(battle);
    }
    if (battle->last_live_nb != -1) {
        my_printf("The player %d (%s) has won.\n", battle->last_live_nb,
        battle->last_live_name);
    }
    return 0;
}