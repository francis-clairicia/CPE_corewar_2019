/*
** EPITECH PROJECT, 2020
** fonction utils for mnemonic
** File description:
** corewar
*/

#include "corewar.h"

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
    return 84;
}

void get_param_type(int *param, int cha)
{
    int i = 1;

    param[0] = 0;
    param[1] = 0;
    param[2] = 0;
    param[3] = 0;
    while (i < 4) {
        if ((cha & 0b11000000) == 0b01000000)
            param[i - 1] = T_REG;
        if ((cha & 0b11000000) == 0b10000000)
            param[i - 1] = T_DIR;
        if ((cha & 0b11000000) == 0b11000000)
            param[i - 1] = T_IND;
        cha = cha << 2;
        i += 1;
    }
}

int read_from_mem(battle_t *battle, int start, int nb_to_read)
{
    int nb = 0;
    int idx = 0;

    while (idx < nb_to_read) {
        nb = (nb << 8);
        nb = nb | battle->mem[(start + idx) % MEM_SIZE];
    }
    return nb;
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
    }
    if (param == T_DIR) {
        nb = read_from_mem(battle, *idx + 1, DIR_SIZE);
        *idx += 4;
    }
    if (param == T_IND) {
        nb = read_from_mem(battle, *idx + 1, IND_SIZE);
        *idx += 2;
    }
    return nb;
}