/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** utils_mnemonic_two.c
*/

#include "corewar.h"

void add_parameter(unsigned char *buffer, int bytes, int size, int start)
{
    unsigned int mask = 0x000000FF;
    int move = 0;

    if (!buffer)
        return;
    for (int i = 1; i < size; i += 1) {
        mask = (mask << 8);
        move += 8;
    }
    for (int i = 0; i < size; i += 1) {
        buffer[start] = ((bytes & mask) >> move);
        start += 1;
        mask = (mask >> 8);
        move -= 8;
    }
}