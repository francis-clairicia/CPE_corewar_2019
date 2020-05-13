/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** read_from_mem.c
*/

#include "corewar.h"

static int read_bytes(battle_t *battle, int start, int nb_to_read)
{
    int nb = 0;

    if (start < 0)
        start = MEM_SIZE - start;
    for (int i = 0; i < nb_to_read; i += 1, start += 1) {
        nb = (nb << 8),
        nb = nb | battle->mem[(start) % MEM_SIZE];
    }
    return (nb);
}

int read_from_mem(battle_t *battle, int start, int nb_to_read)
{
    if (nb_to_read == sizeof(char))
        return ((char)read_bytes(battle, start, 1));
    if (nb_to_read == sizeof(short))
        return ((short)read_bytes(battle, start, 2));
    return (read_bytes(battle, start, 4));
}