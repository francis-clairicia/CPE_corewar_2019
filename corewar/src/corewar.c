/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** corewar.c
*/

#include "corewar.h"
#include "macro.h"
#include "my.h"

int corewar(char **av)
{
    champ_t *champ = NULL;
    battle_t *battle = IMALLOC(battle, sizeof(battle_t));

    if (parse_arg(av, champ, battle) == 84)
        return 84;
    return 0;
}