/*
** EPITECH PROJECT, 2020
** mnemonic aff
** File description:
** corewar
*/

#include "corewar.h"
#include "mymacros.h"

int mne_aff(param_t const *params, champ_t *champ, battle_t *battle)
{
    ICHECK(params)
    ICHECK(champ)
    ICHECK(battle)
    my_putchar(champ->reg[params->value[0] - 1] % 256);
    return 0;
}