/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** add_champion.c
*/

#include "corewar.h"
#include "macro.h"

static void add_champ2(champ_t *tmp, utils_parser_t *up)
{
    tmp->carry = 0;
    tmp->live = 0;
    tmp->pc = 0;
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

op_t *add_empty_op(void)
{
    op_t *op = PMALLOC(op, sizeof(op_t));

    op->code = '\0';
    op->comment = NULL;
    op->mnemonique = NULL;
    op->nbr_args = '\0';
    op->nbr_cycles = 0;
    op->type[0] = '\0';
    return op;
}

champ_t *add_champ(champ_t **champ, char *brut_name, utils_parser_t *up)
{
    champ_t *tmp = PMALLOC(tmp, sizeof(champ_t));
    static int last_address = 0;
    static int nb = 0;
    static int nb_prog = 0;

    tmp->header = add_empty_header();
    tmp->op = add_empty_op();
    last_address = (up->bool_address == true) ? up->address : last_address;
    nb = (up->bool_champ == true) ? up->nb_champ : nb;
    tmp->brut_name = my_revstr(brut_name);
    tmp->address = (up->bool_address == true) ? up->address % MEM_SIZE :
    ++last_address * nb_prog;
    tmp->nb_champ = nb++;
    for (; tmp->address > MEM_SIZE; tmp->address -= MEM_SIZE);
    tmp->reg = PMALLOC(tmp->reg, sizeof(int) * (REG_NUMBER));
    add_champ2(tmp, up);
    tmp->next = (nb_prog == 0) ? NULL : *champ;
    nb_prog++;
    return tmp;
}