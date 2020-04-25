/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** args.c
*/

#include "corewar.h"
#include "macro.h"
#include "my.h"

int dump_arg(char **av, battle_t *battle, utils_parser_t *up)
{
    static bool check = false;

    if (check == true || !av[up->i + 1])
        return 84;
    if (my_str_isnum(av[up->i + 1]) == 0)
        return 84;
    battle->dump = my_getnbr(av[up->i + 1]);
    if (battle->dump < 1)
        return 84;
    up->i += 1;
    check = true;
    return 0;
}

int n_arg(char **av, __attribute__((unused)) battle_t *battle,
            utils_parser_t *up)
{
    if (up->bool_champ == true || !av[up->i + 1])
        return 84;
    if (my_str_isnum(av[up->i + 1]) == 0)
        return 84;
    up->nb_champ = my_getnbr(av[up->i + 1]);
    if (up->nb_champ < 1)
        return 84;
    up->i += 1;
    up->bool_champ = true;
    return 0;
}

int a_arg(char **av, __attribute__((unused)) battle_t *battle, utils_parser_t *up)
{
    if (up->bool_address == true || !av[up->i + 1])
        return 84;
    if (my_str_isnum(av[up->i + 1]) == 0)
        return 84;
    up->address = my_getnbr(av[up->i + 1]);
    if (up->address < 1)
        return 84;
    up->i += 1;
    up->bool_address = true;
    return 0;
}