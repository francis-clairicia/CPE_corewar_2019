/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** main.c
*/

#include "asm.h"

int main(int ac, char **av)
{
    if (ac != 2)
        return 84;
    return (assembly(av[1]));
}