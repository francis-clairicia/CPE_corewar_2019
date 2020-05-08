/*
** EPITECH PROJECT, 2019
** asm
** File description:
** add_instructions_functions.c
*/

#include "asm.h"
#include "my.h"

void add_parameter(char *buffer, int bytes, int size, int *start)
{
    unsigned int mask = 0x000000FF;
    int move = 0;

    if (!buffer || !start)
        return;
    for (int i = 1; i < size; i += 1) {
        mask = (mask << 8);
        move += 8;
    }
    for (int i = 0; i < size; i += 1) {
        buffer[*start] = ((bytes & mask) >> move);
        *start += 1;
        mask = (mask >> 8);
        move -= 8;
    }
}