/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** corewar.h
*/

#ifndef COREWAR_H
#define COREWAR_H

#include "op.h"
#include "stdbool.h"

typedef struct champ_s
{
    header_t *header;
    op_t *op;
    int *reg;
    int pc;
    int carry;
    int live;
    char *brut_name;
    int nb;
    int nb_champ;
    struct champ_s *next;
} champ_t;

typedef struct battle_s
{
    int nb_champ;
    int dump;
    int cycle;
    char *mem;
} battle_t;

typedef struct utils_parser_s
{
    int i;
    int nb_champ;
    int address;
    bool bool_champ;
    bool bool_address;
} utils_parser_t;

typedef struct parser_s
{
    char *arg;
    int (*parse)(char **, battle_t *, utils_parser_t *);
} parser_t;

int corewar(char **av);
int parse_arg(char **av, champ_t *champ, battle_t *battle);
int dump_arg(char **av, battle_t *battle, utils_parser_t *up);
int n_arg(char **av, battle_t *battle, utils_parser_t *up);
int a_arg(char **av, battle_t *battle, utils_parser_t *up);
champ_t *add_champ(champ_t *champ, char *brut_name, utils_parser_t *up);

void print_help(int syntax);
int help(int ac, char **av);

#endif