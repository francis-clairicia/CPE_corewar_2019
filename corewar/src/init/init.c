/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** init.c
*/

#include "corewar.h"
#include "macro.h"
#include "string.h"

utils_parser_t *init_util_parser(void)
{
    utils_parser_t *up = PMALLOC(up, sizeof(utils_parser_t));

    up->address = -1;
    up->nb_champ = -1;
    up->bool_address = false;
    up->bool_champ = false;
    up->i = 1;
    return up;
}

battle_t *init_empty_battle(void)
{
    battle_t *battle = PMALLOC(battle, sizeof(battle_t));

    battle->cycle = 0;
    battle->dump = 0;
    battle->mem = PMALLOC(battle->mem, sizeof(char) * (MEM_SIZE + 1));
    battle->mem[MEM_SIZE] = '\0';
    battle->nb_champ = 0;
    return battle;
}