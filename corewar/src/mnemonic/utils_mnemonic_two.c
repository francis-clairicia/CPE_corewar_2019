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
        buffer[start % MEM_SIZE] = ((bytes & mask) >> move);
        start += 1;
        mask = (mask >> 8);
        move -= 8;
    }
}

void move_pc(champ_t *champ, int *param)
{
    int idx = 0;

    while (idx < MAX_ARGS_NUMBER) {
        if (param[idx] == T_REG)
            champ->pc += 1;
        if (param[idx] == T_DIR)
            champ->pc += DIR_SIZE;
        if (param[idx] == T_IND)
            champ->pc += IND_SIZE;
        idx += 1;
    }
    champ->pc += 2;
}

void move_pc_special(champ_t *champ, int *param)
{
    int idx = 0;

    while (idx < MAX_ARGS_NUMBER) {
        if (param[idx] == T_REG)
            champ->pc += 1;
        if (param[idx] == T_DIR)
            champ->pc += 2;
        if (param[idx] == T_IND)
            champ->pc += IND_SIZE;
        idx += 1;
    }
    champ->pc += 2;
}