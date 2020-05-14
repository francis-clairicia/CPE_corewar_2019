/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** corewar.h
*/

#ifndef COREWAR_H
#define COREWAR_H

#include <stdbool.h>
#include <stdio.h>
#include "op.h"

typedef struct champ_s
{
    FILE *fp;
    int status;
    header_t *header;
    op_t op;
    int reg[REG_NUMBER];
    int nb_address;
    int pc;
    int carry;
    bool live;
    char *brut_name;
    int nb_champ;
    bool act;
    bool die;
    bool parent;
    struct champ_s *children;
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
    bool graphic;
    unsigned char *mem;
    champ_t *champ_tab[4];
    char *last_live_name;
    int last_live_nb;
    int tot_cycle;
    bool draw_dump;
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

typedef struct parameter
{
    args_type_t type[MAX_ARGS_NUMBER];
    int value[MAX_ARGS_NUMBER];
} param_t;

int corewar(char **av);
int parse_arg(char **av, champ_t **champ, battle_t *battle);
int dump_arg(char **av, battle_t *battle, utils_parser_t *up);
int flag_n(char **av, battle_t *battle, utils_parser_t *up);
int flag_a(char **av, battle_t *battle, utils_parser_t *up);
int flag_g(char **av, battle_t *battle, utils_parser_t *up);
int flag_h(char **av, battle_t *battle, utils_parser_t *up);
battle_t *init_empty_battle(void);
utils_parser_t *init_util_parser(void);
void free_all(champ_t *champ, battle_t *battle);
void free_champ(champ_t *champ);
void free_battle(battle_t *battle);
int check_champ(champ_t **champ, battle_t *battle);
champ_t *add_champ(champ_t **champ, char *brut_name, utils_parser_t *up);
void sort_champ_list(champ_t **champ);
int reverse_number(int nb);
int fill_mem(champ_t *champ, battle_t *battle);
void print_dump(unsigned char *memory);
int game_loop(champ_t *champ, battle_t *battle);
int game_act(battle_t *battle, champ_t *champ);
bool no_end(battle_t *battle, champ_t *champ);
void champ_address(champ_t *champ, int nb_champ);
void end_loop(battle_t *battle);

void print_help(int syntax);
int help(int ac, char **av);
int ret_putstr_fd(int fd, char *str);

int launch_mnemonic(battle_t *battle, champ_t *champ);
typedef int (*mnemonic_t)(param_t const *params, champ_t *, battle_t *);
int mne_add(param_t const *params, champ_t *champ, battle_t *battle);
int mne_aff(param_t const *params, champ_t *champ, battle_t *battle);
int mne_and(param_t const *params, champ_t *champ, battle_t *battle);
int mne_fork(param_t const *params, champ_t *champ, battle_t *battle);
int mne_ld(param_t const *params, champ_t *champ, battle_t *battle);
int mne_ldi(param_t const *params, champ_t *champ, battle_t *battle);
int mne_lfork(param_t const *params, champ_t *champ, battle_t *battle);
int mne_live(param_t const *params, champ_t *champ, battle_t *battle);
int mne_lld(param_t const *params, champ_t *champ, battle_t *battle);
int mne_lldi(param_t const *params, champ_t *champ, battle_t *battle);
int mne_or(param_t const *params, champ_t *champ, battle_t *battle);
int mne_st(param_t const *params, champ_t *champ, battle_t *battle);
int mne_sti(param_t const *params, champ_t *champ, battle_t *battle);
int mne_sub(param_t const *params, champ_t *champ, battle_t *battle);
int mne_xor(param_t const *params, champ_t *champ, battle_t *battle);
int mne_zjmp(param_t const *params, champ_t *champ, battle_t *battle);

void get_param_type(param_t *params, unsigned char coding_byte);
bool valid_params(param_t const *params, int op_code);
int set_param_values(param_t *params, unsigned char *memory,
    int start, int dir_size);
int set_param_values_without_cb(param_t *params, unsigned char *memory,
    int start, char const *mnemonic);
int read_from_mem(unsigned char *memory, int start, int nb_to_read);
void add_parameter(unsigned char *buffer, int bytes, int size, int start);
champ_t *get_child(champ_t *champ, int child_pc);
int normal_get_value(unsigned char *mem, champ_t *champ, param_t *param,
                            int *idx);

#define get_coding_byte(mem, pc) \
    (unsigned char)read_from_mem(mem, pc, sizeof(char))

#define IS_A_REGISTER(r_nb) (r_nb >= 1 && r_nb <= REG_NUMBER)

#endif