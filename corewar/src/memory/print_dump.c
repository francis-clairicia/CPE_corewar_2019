/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** print_dump.c
*/

#include "corewar.h"
#include "mymacros.h"

void print_dump(unsigned char *memory)
{
    static bool check_first = false;

    if (check_first == true)
        my_putchar('\n');
    check_first = true;
    for (int i = 0; i < MEM_SIZE;) {
        my_printf("%-5X:", i);
        for (int j = 0; j < 32; j++, i++) {
            my_printf(" %02X", memory[i]);
        }
        my_putchar('\n');
    }
}