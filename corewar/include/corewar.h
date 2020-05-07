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
    int status;
    header_t *header;
    op_t op;
    int *reg;
    int nb_address;
    int pc;
    int carry;
    bool live;
    char *brut_name;
    int nb_champ;
    struct champ_s *next;
} champ_t;

typedef struct battle_s
{
    int nb_champ;
    int dump;
    int cycle;
    int cycle_die;
    int nb_live;
    bool *check_mem;
    unsigned char *mem;
    champ_t *last_live;
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
int parse_arg(char **av, champ_t **champ, battle_t *battle);
int dump_arg(char **av, battle_t *battle, utils_parser_t *up);
int n_arg(char **av, battle_t *battle, utils_parser_t *up);
int a_arg(char **av, battle_t *battle, utils_parser_t *up);
battle_t *init_empty_battle(void);
utils_parser_t *init_util_parser(void);
void free_all(champ_t *champ, battle_t *battle);
void free_champ(champ_t *champ);
void free_battle(battle_t *battle);
int check_champ(champ_t **champ, battle_t *battle);
champ_t *add_champ(champ_t **champ, char *brut_name, utils_parser_t *up);
void sort_champ_list(champ_t **champ);
int rev_nb(int nb);
int fill_mem(champ_t *champ, battle_t *battle);
void print_dump(unsigned char *memory);
int game_loop(champ_t *champ, battle_t *battle);
bool no_end(battle_t *battle);

void print_help(int syntax);
int help(int ac, char **av);
int ret_putstr_fd(int fd, char *str);

int mne_add(champ_t *champ, battle_t *battle);
int mne_aff(champ_t *champ, battle_t *battle);
int mne_and(champ_t *champ, battle_t *battle);
int mne_fork(champ_t *champ, battle_t *battle);
int mne_ld(champ_t *champ, battle_t *battle);
int mne_ldi(champ_t *champ, battle_t *battle);
int mne_lfork(champ_t *champ, battle_t *battle);
int mne_live(champ_t *champ, battle_t *battle);
int mne_lld(champ_t *champ, battle_t *battle);
int mne_lldi(champ_t *champ, battle_t *battle);
int mne_or(champ_t *champ, battle_t *battle);
int mne_st(champ_t *champ, battle_t *battle);
int mne_sti(champ_t *champ, battle_t *battle);
int mne_sub(champ_t *champ, battle_t *battle);
int mne_xor(champ_t *champ, battle_t *battle);
int mne_zjmp(champ_t *champ, battle_t *battle);

int is_register(int nb);
int get_value(champ_t *champ, battle_t *battle);
int puissance(int number, int nb);

#endif