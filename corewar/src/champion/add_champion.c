/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** add_champion.c
*/

#include "corewar.h"
#include "mymacros.h"

static void add_champ_two(champ_t *tmp, utils_parser_t *up)
{
    tmp->pc = tmp->nb_address;
    up->address = 0;
    up->nb_champ = 0;
    up->bool_address = false;
    up->bool_champ = false;
}

header_t *add_empty_header(void)
{
    header_t *header = PMALLOC(header, sizeof(header_t));

    my_memset(header, 0, sizeof(header_t));
    return header;
}

champ_t *add_champ(champ_t **champ, char *brut_name, utils_parser_t *up)
{
    champ_t *tmp = PMALLOC(tmp, sizeof(champ_t));
    static int nb_prog = 0;

    my_memset(tmp, 0, sizeof(champ_t));
    tmp->header = add_empty_header();
    tmp->brut_name = my_revstr(brut_name);
    tmp->nb_address = (up->bool_address == true) ? up->address % MEM_SIZE : -1;
    tmp->nb_champ = (up->bool_champ == true) ? up->nb_champ : 0;
    tmp->reg[0] = tmp->nb_champ;
    add_champ_two(tmp, up);
    tmp->next = (nb_prog == 0) ? NULL : *champ;
    nb_prog++;
    return tmp;
}