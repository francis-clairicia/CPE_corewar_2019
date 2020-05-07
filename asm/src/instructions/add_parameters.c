/*
** EPITECH PROJECT, 2019
** asm
** File description:
** add_instructions_functions.c
*/

#include "asm.h"
#include "my.h"

void add_register_parameter(char *buffer, int parameter, int *start)
{
    char one_byte = parameter;

    if (!buffer || !start)
        return;
    buffer[*start] = one_byte;
    *start += SIZE_TYPE[T_REG];
}

void add_direct_parameter(char *buffer, int parameter, int *start)
{
    int four_bytes = parameter;

    if (!buffer || !start)
        return;
    buffer[*start + 0] = ((four_bytes & 0xFF000000) >> 24);
    buffer[*start + 1] = ((four_bytes & 0x00FF0000) >> 16);
    buffer[*start + 2] = ((four_bytes & 0x0000FF00) >> 8);
    buffer[*start + 3] = ((four_bytes & 0x000000FF));
    *start += SIZE_TYPE[T_DIR];
}

void add_indirect_parameter(char *buffer, int parameter, int *start)
{
    short two_bytes = parameter;

    if (!buffer || !start)
        return;
    buffer[*start + 0] = ((two_bytes & 0xFF00) >> 8);
    buffer[*start + 1] = ((two_bytes & 0x00FF));
    *start += SIZE_TYPE[T_IND];
}