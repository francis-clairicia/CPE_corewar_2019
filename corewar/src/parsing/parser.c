/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** parser.c
*/

#include "corewar.h"
#include "macro.h"
#include "my.h"
#include <stdbool.h>

static const parser_t parser_list[] =
{
    {"-dump", &dump_arg},
    {"-n", &n_arg},
    {"-a", &a_arg},
    {NULL, NULL}
};

static void add_champ2(champ_t *tmp, utils_parser_t *up)
{
    tmp->carry = 0;
    tmp->header = NULL;
    tmp->live = 0;
    tmp->op = NULL;
    tmp->pc = 0;
    up->address = -1;
    up->nb_champ = -1;
    up->bool_address = false;
    up->bool_champ = false;
}

static champ_t *add_champ(champ_t *champ, char *brut_name, utils_parser_t *up)
{
    champ_t *tmp = PMALLOC(tmp, sizeof(champ_t));
    static int last_address = 0;
    static int nb = 0;
    static int nb_prog = 0;

    if (up->nb_champ < -1 || up->address < -1)
        return NULL;
    last_address = (up->address != -1) ? up->address : last_address;
    nb = (up->nb_champ != -1) ? up->nb_champ : nb;
    tmp->brut_name = brut_name;
    tmp->address = (up->address != -1) ? up->address % MEM_SIZE :
    last_address * nb_prog;
    tmp->nb_champ = nb++;
    tmp->nb = nb_prog++ - 1;
    for (; tmp->address > MEM_SIZE; tmp->address -= 1);
    tmp->reg = PMALLOC(tmp->reg, sizeof(int) * (REG_NUMBER));
    add_champ2(tmp, up);
    tmp->next = champ;
    return tmp;
}

static int check_all_args(char **av, battle_t *battle,
                        utils_parser_t *up, int j)
{
    if (parser_list[j].parse(av, battle, up) == 84) {
        print_help(2);
        return 84;
    }
    return 0;
}

static int parse_arg_loop(char **av, battle_t *battle,
                        utils_parser_t *up, champ_t *champ)
{
    bool check = false;

    for (int j = 0; parser_list[j].arg; j++) {
        if (my_strcmp(av[up->i], parser_list[j].arg) == 0) {
            IRETURN(check_all_args(av, battle, up, j))
            check = true;
            break;
        }
    }
    if (check == false) {
        if (my_strncmp(my_revstr(av[up->i]), "roc.", 4) == 0) {
            ICHECK((champ = add_champ(champ, av[up->i], up)));
            battle->nb_champ += 1;
        } else {
            my_putstr_fd(2, "File name should be a .cor\n");
            return 84;
        }
    }
    return 0;
}

int parse_arg(char **av, champ_t *champ, battle_t *battle)
{
    utils_parser_t *up = NULL;

    ICHECK((up = init_util_parser()));
    for (; av[up->i]; up->i += 1) {
        IRETURN(parse_arg_loop(av, battle, up, champ))
    }
    if (battle->nb_champ < 2) {
        my_putstr_fd(2, "The number of champion load is below the limit.\n");
        return 84;
    }
    if (battle->nb_champ > 4) {
        my_putstr_fd(2, "The number of champion load is above the limit.\n");
        return 84;
    }
    free(up);
    return 0;
}