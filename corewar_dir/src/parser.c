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

champ_t *add_champ(champ_t *champ, char *brut_name, utils_parser_t *up)
{
    champ_t *tmp = PMALLOC(tmp, sizeof(champ_t));
    static int last_address = 0;
    static int nb = 0;
    static int nb_prog = 0;

    if (up->nb_champ < -1 || up->address < -1)
        return NULL;
    if (up->address != -1)
        last_address = up->address;
    if (up->nb_champ != -1)
        nb = up->nb_champ;
    tmp->brut_name = brut_name;
    tmp->carry = 0;
    tmp->header = NULL;
    tmp->live = 0;
    tmp->nb = nb_prog - 1;
    tmp->nb_champ = nb;
    tmp->op = NULL;
    if (up->address != -1)
        tmp->pc = up->address % MEM_SIZE;
    else
        tmp->pc = last_address * nb_prog;
    while (tmp->pc > MEM_SIZE)
        tmp->pc -= MEM_SIZE;
    tmp->reg = PMALLOC(tmp->reg, sizeof(int) * (REG_NUMBER));
    nb_prog++;
    nb++;
    up->address = -1;
    up->nb_champ = -1;
    up->bool_address = false;
    up->bool_champ = false;
    tmp->next = champ;
    return tmp;
}

utils_parser_t *init_util_parser(void)
{
    utils_parser_t *up = PMALLOC(up, sizeof(utils_parser_t));

    up->address = -1;
    up->nb_champ = -1;
    up->bool_address = false;
    up->bool_champ = false;
    up->i = 1;
    return up;
}

int parse_arg(char **av, champ_t *champ, battle_t *battle)
{
    bool check = false;
    utils_parser_t *up = init_util_parser();
    battle->mem = IMALLOC(battle->mem, sizeof(char) * (MEM_SIZE + 1));
    battle->nb_champ = 0;

    if (!up) {
        print_help(2);
        return 84;
    }
    for (; av[up->i]; up->i += 1) {
        for (int j = 0; parser_list[j].arg; j++) {
            if (my_strcmp(av[up->i], parser_list[j].arg) == 0) {
                if (parser_list[j].parse(av, battle, up) == 84) {
                    print_help(2);
                    return 84;
                }
                check = true;
                break;
            }
        }
        if (check == false) {
            if (my_strncmp(my_revstr(av[up->i]), "roc.", 4) == 0) {
                champ = add_champ(champ, av[up->i], up);
                battle->nb_champ += 1;
                if (!champ) {
                    print_help(2);
                    return 84;
                }
            } else {
                print_help(2);
                return 84;
            }
        }
        check = false;
    }
    if (battle->nb_champ < 2) {
        my_putstr_fd(2, "The number of champion load is below the limit.\n");
        return 84;
    }
    if (battle->nb_champ > 4) {
        my_putstr_fd(2, "The number of champion load is above the limit.\n");
        return 84;
    }
    return 0;
}