/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** parser.c
*/

#include "corewar.h"
#include "mymacros.h"

static const parser_t parser_list[] =
{
    {"-dump", &dump_arg},
    {"-n", &flag_n},
    {"-a", &flag_a},
    {"-g", &flag_g},
    {NULL, NULL}
};

static int check_all_args(char **av, battle_t *battle,
                        utils_parser_t *up, int j)
{
    if (parser_list[j].parse(av, battle, up) == 84) {
        return 84;
    }
    return 0;
}

static int parse_arg_loop(char **av, battle_t *battle,
                        utils_parser_t *up, champ_t **champ)
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
            ICHECK((*champ = add_champ(champ, av[up->i], up)));
            battle->champ_tab[battle->nb_champ] = *champ;
            battle->nb_champ += 1;
        } else {
            return ret_putstr_fd(2, "File name should be a .cor\n");
        }
    }
    return 0;
}

int parse_arg(char **av, champ_t **champ, battle_t *battle)
{
    utils_parser_t *up = NULL;

    ICHECK((up = init_util_parser()));
    for (; av[up->i]; up->i += 1) {
        IRETURN(parse_arg_loop(av, battle, up, champ))
    }
    free(up);
    if (battle->nb_champ < 2) {
        return ret_putstr_fd(2, "The number of champion load is below the "
        "limit.\n");
    }
    if (battle->nb_champ > 4) {
        return ret_putstr_fd(2, "The number of champion load is above the "
        "limit.\n");
    }
    champ_address(*champ, battle->nb_champ);
    return 0;
}