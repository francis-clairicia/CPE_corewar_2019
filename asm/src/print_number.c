/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** print_number.c
*/

#include <stdio.h>
#include "asm.h"

void print_number(int nb, FILE *file)
{
    int reversed_nb = REVERSED_NB(nb);

    if (file != NULL)
        fwrite(&reversed_nb, sizeof(int), 1, file);
}