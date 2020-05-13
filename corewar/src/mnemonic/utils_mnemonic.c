/*
** EPITECH PROJECT, 2020
** fonction utils for mnemonic
** File description:
** corewar
*/

#include "corewar.h"
#include "mymacros.h"

int pows(int number, int nb)
{
    if (nb == 0)
        return 1;
    return number * pows(number, nb - 1);
}

int is_register(int nb)
{
    if (nb >= 1 && nb <= REG_NUMBER)
        return 1;
    return 0;
}

int *get_param_type(int cha)
{
    int i = 0;
    int *param = PMALLOC(param, sizeof(int) * MAX_ARGS_NUMBER);
    my_memset(param, 0, MAX_ARGS_NUMBER * sizeof(int));

    while (i < MAX_ARGS_NUMBER) {
        if ((cha & 0b11000000) == 0b01000000)
            param[i] = T_REG;
        if ((cha & 0b11000000) == 0b10000000)
            param[i] = T_DIR;
        if ((cha & 0b11000000) == 0b11000000)
            param[i] = T_IND;
        cha = cha << 2;
        i += 1;
    }
    return param;
}

int get_three_value(battle_t *battle, champ_t *champ, int *idx, int param)
{
    int nb = 0;

    if (*idx == -1)
        return 0;
    if (param == T_REG) {
        if (is_register(battle->mem[(*idx + 1) % MEM_SIZE])) {
            nb = champ->reg[(battle->mem[(*idx + 1) % MEM_SIZE]) - 1];
            *idx += 1;
        } else
            *idx = -1;
    } if (param == T_DIR) {
        nb = read_from_mem(battle, *idx + 1, DIR_SIZE);
        *idx += DIR_SIZE;
    } if (param == T_IND) {
        nb = read_from_mem(battle, *idx + 1, IND_SIZE);
        nb = read_from_mem(battle, champ->pc + nb, IND_SIZE);
        *idx += IND_SIZE;
    }
    return nb;
}