/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** check_env.c
*/

#include "ncurses_bonus.h"

bool no_env(char **env)
{
    if (!env)
        return true;
    for (int i = 0; env[i]; i++) {
        if (strncmp(env[i], "TERM=", 5) == 0)
            return false;
    }
    return true;

}