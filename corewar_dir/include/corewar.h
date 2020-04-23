/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** corewar.h
*/

#ifndef COREWAR_H
#define COREWAR_H

#include "op.h"

typedef struct champ_s
{
    header_t *header;
    op_t *op;
    int reg;
    int pc;
    int carry;
    int live;
    char *name;
    int nb;
    int nb_champ;
    struct champ_s *next;
} champ_t;

typedef struct battle_s
{
    int dump;
    int cycle;
    char mem[MEM_SIZE];
} battle_t;

int corewar(int ac, char **av);

void print_help(int syntax);
int help(int ac, char **av);

#endif