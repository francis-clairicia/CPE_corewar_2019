/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** main.c
*/

#include "ncurses_bonus.h"

int main(int ac, __attribute__((unused)) char **av, char **env)
{
    if (ac != 1 || no_env(env))
        return 84;
    return bonus_vm();
}