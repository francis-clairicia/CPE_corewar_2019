/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** corewar.c
*/

#include "corewar.h"
#include "mymacros.h"

int corewar(char **av)
{
    champ_t *champ = NULL;
    battle_t *battle = NULL;

    ICHECK((battle = init_empty_battle()));
    IRETURN(parse_arg(av, &champ, battle));
    IRETURN(check_champ(&champ, battle));
    IRETURN(fill_mem(champ, battle));
    free_all(champ, battle);
    return 0;
}