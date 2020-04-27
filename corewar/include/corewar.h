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
#include "stdio.h"

typedef struct champ_s
{
    FILE *fp;
    int wait;
    header_t *header;
    op_t *op;
    int *reg;
    int address;
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
battle_t *init_empty_battle(void);
utils_parser_t *init_util_parser(void);

void print_help(int syntax);
int help(int ac, char **av);

#endif