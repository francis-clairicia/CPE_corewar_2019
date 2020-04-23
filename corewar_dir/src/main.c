/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** main.c
*/

#include "corewar.h"

int main(int ac, char **av)
{
    if (ac < 2 || ac > 14){
        print_help(2);
        return 84;
    } 
    if (help(ac, av))
        return 0;
    return corewar(ac, av);
}