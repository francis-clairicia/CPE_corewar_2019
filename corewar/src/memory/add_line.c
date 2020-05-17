/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** add_line.c
*/

#include "corewar.h"
#include "mymacros.h"

void add_line(battle_t *battle, int memory_id)
{
    int line = 0;
    int max_nb_lines = MEM_SIZE / 32;

    if (!battle || battle->graphic == false)
        return;
    line = (memory_id % MEM_SIZE) / 32;
    if (line < 0)
        line += max_nb_lines;
    if (my_node_from_data(battle->lines, line, int) == NULL)
        my_append_to_list(&battle->lines, line, int);
}