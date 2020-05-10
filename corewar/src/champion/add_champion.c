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
    tmp->carry = 0;
    tmp->live = false;
    tmp->pc = (tmp->nb_address != -1) ? tmp->nb_address : -1;
    tmp->act = false;
    tmp->die = false;
    tmp->status = 0;
    up->address = 0;
    up->nb_champ = 0;
    up->bool_address = false;
    up->bool_champ = false;
}

header_t *add_empty_header(void)
{
    header_t *header = PMALLOC(header, sizeof(header_t));

    header->magic = 0;
    header->comment[0] = '\0';
    header->prog_name[0] = '\0';
    header->prog_size = 0;
    return header;
}

champ_t *add_champ(champ_t **champ, char *brut_name, utils_parser_t *up)
{
    champ_t *tmp = PMALLOC(tmp, sizeof(champ_t));
    static int nb_prog = 0;

    tmp->header = add_empty_header();
    tmp->op = op_tab[16];
    tmp->brut_name = my_revstr(brut_name);
    tmp->nb_address = (up->bool_address == true) ? up->address % MEM_SIZE : -1;
    tmp->nb_champ = (up->bool_champ == true) ? up->nb_champ : 0;
    tmp->reg = PMALLOC(tmp->reg, sizeof(int) * (REG_NUMBER));
    my_memset(tmp->reg, 0, REG_NUMBER);
    tmp->reg[0] = tmp->nb_champ;
    add_champ_two(tmp, up);
    tmp->next = (nb_prog == 0) ? NULL : *champ;
    nb_prog++;
    return tmp;
}