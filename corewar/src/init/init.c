/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** init.c
*/

#include "corewar.h"
#include "mymacros.h"
#include "string.h"

utils_parser_t *init_util_parser(void)
{
    utils_parser_t *up = PMALLOC(up, sizeof(utils_parser_t));

    up->address = 0;
    up->nb_champ = 0;
    up->bool_address = false;
    up->bool_champ = false;
    up->i = 1;
    return up;
}

battle_t *init_empty_battle(void)
{
    battle_t *battle = PMALLOC(battle, sizeof(battle_t));

    battle->cycle = 0;
    battle->cycle_die = CYCLE_TO_DIE;
    battle->nb_live = 0;
    battle->dump = -1;
    battle->last_live = NULL;
    battle->mem = PMALLOC(battle->mem, sizeof(char) * (MEM_SIZE + 1));
    my_memset(battle->mem, 0, MEM_SIZE);
    battle->check_mem = PMALLOC(battle->mem, sizeof(bool) * (MEM_SIZE));
    my_memset(battle->check_mem, 0, MEM_SIZE);
    battle->mem[MEM_SIZE] = '\0';
    battle->nb_champ = 0;
    for (int i = 0; i < 4; i++)
        battle->champ_tab[i] = NULL;
    return battle;
}