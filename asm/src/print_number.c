/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** print_number.c
*/

#include <stdio.h>

static int rev_nb(int nb)
{
    int result = 0;
    int mask = 0;

    for (int i = 0; i < 32; i += 8) {
        mask = ((nb & (0xff << i)) >> i);
        result |= (mask << (24 - i));
    }
    return result;
}

void print_number(int nb, FILE *file)
{
    int reversed_nb = rev_nb(nb);

    if (file != NULL)
        fwrite(&reversed_nb, sizeof(int), 1, file); 
}