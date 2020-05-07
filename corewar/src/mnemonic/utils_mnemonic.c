/*
** EPITECH PROJECT, 2020
** fonction utils for mnemonic
** File description:
** corewar
*/

#include "corewar.h"

int puissance(int number, int nb)
{
    if (nb == 0)
        return 1;
    return number * puissance(number, nb - 1);
}

int get_value(champ_t *champ, battle_t *battle)
{
    int nb = 0;
    
    nb = battle->mem[champ->pc] * puissance(256, 3)
        + battle->mem[champ->pc + 1] * puissance(256, 2)
        + battle->mem[champ->pc + 2] * puissance(256, 1)
        + battle->mem[champ->pc + 3] * puissance(256, 0);
    champ->pc += 4;
    return nb;
}

int is_register(int nb)
{
    if (nb >= 1 && nb <= REG_NUMBER)
        return 1;
    return 84;
}