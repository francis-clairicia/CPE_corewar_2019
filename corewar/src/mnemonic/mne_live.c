/*
** EPITECH PROJECT, 2020
** mnemonic live
** File description:
** corewar
*/

#include "corewar.h"
#include "my.h"

int mne_live(champ_t *champ, battle_t *battle)
{
    int param = read_from_mem(battle, champ->pc + 1, DIR_SIZE);

    if (param >= 1 && param <= battle->nb_champ) {
        my_printf("The player %d (%s) is alive.\n",
        battle->champ_tab[param - 1]->nb_champ,
        battle->champ_tab[param - 1]->header->prog_name);
        battle->champ_tab[param - 1]->live = true;
        battle->last_live = battle->champ_tab[param - 1];
        battle->nb_live += 1;
    }
    champ->pc += 5;
    return 0;
}