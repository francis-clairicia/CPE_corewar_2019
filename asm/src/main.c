/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** main.c
*/

#include "asm.h"

int main(int ac, char **av)
{
    if (ac != 2) {
        return 84;
    } else {
        assembly(av[1]);
    }
    return (0);
}