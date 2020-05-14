/*
** EPITECH PROJECT, 2020
** fonction utils for mnemonic
** File description:
** corewar
*/

#include "corewar.h"
#include "mymacros.h"

void get_param_type(param_t *params, unsigned char coding_byte)
{
    int i = 0;

    if (!params)
        return;
    while (i < MAX_ARGS_NUMBER) {
        if ((coding_byte & 0b11000000) == 0b01000000)
            params->type[i] = T_REG;
        if ((coding_byte & 0b11000000) == 0b10000000)
            params->type[i] = T_DIR;
        if ((coding_byte & 0b11000000) == 0b11000000)
            params->type[i] = T_IND;
        coding_byte = coding_byte << 2;
        i += 1;
    }
}

bool valid_params(param_t const *params, int op_code)
{
    op_t *op = &op_tab[op_code - 1];

    if (!params)
        return (false);
    for (int i = 0; i < op->nbr_args; i += 1) {
        if ((params->type[i] & op->type[i]) == 0)
            return (false);
    }
    return (true);
}

int set_param_values(param_t *params, unsigned char *memory,
    int start, int dir_size)
{
    int size = 0;
    int total = 0;

    for (int i = 0; params && memory && i < MAX_ARGS_NUMBER; i += 1) {
        size = 0;
        if (params->type[i] == T_REG)
            size = sizeof(char);
        if (params->type[i] == T_DIR)
            size = dir_size;
        if (params->type[i] == T_IND)
            size = IND_SIZE;
        params->value[i] = read_from_mem(memory, start, size);
        start += size;
        total += size;
    }
    return (total);
}

int set_param_values_without_cb(param_t *params, unsigned char *memory,
    int start, char const *mnemonic)
{
    int size = 0;

    if (!params || !mnemonic)
        return (0);
    size = (my_strcmp(mnemonic, "live") == 0) ? 4 : 2;
    params->value[0] = read_from_mem(memory, start, size);
    return (size);
}

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
    if (start < 0)
        start = MEM_SIZE - start;
    for (int i = 0; i < size; i += 1) {
        buffer[start % MEM_SIZE] = ((bytes & mask) >> move);
        start += 1;
        mask = (mask >> 8);
        move -= 8;
    }
}