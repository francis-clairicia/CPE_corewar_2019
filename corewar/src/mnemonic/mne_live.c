/*
** EPITECH PROJECT, 2020
** mnemonic live
** File description:
** corewar
*/

#include "corewar.h"
#include "mymacros.h"

int mne_live(param_t const *param, champ_t *champ, battle_t *battle)
{
    ICHECK(param || !champ || !battle);
    int val = param->value[0];

    if (val >= 1 && val <= battle->nb_champ &&
    battle->champ_tab[val - 1]->die == false) {
        my_printf("The player %d (%s) is alive.\n",
        battle->champ_tab[val - 1]->nb_champ,
        battle->champ_tab[val - 1]->header->prog_name);
        battle->champ_tab[val - 1]->live = true;
        battle->last_live_name =
        battle->champ_tab[val - 1]->header->prog_name;
        battle->last_live_nb = battle->champ_tab[val - 1]->nb_champ;
        battle->nb_live += 1;
    }
    return 0;
}