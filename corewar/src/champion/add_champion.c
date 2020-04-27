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
    tmp->header = NULL;
    tmp->live = 0;
    tmp->op = NULL;
    tmp->pc = 0;
    up->address = 0;
    up->nb_champ = 0;
    up->bool_address = false;
    up->bool_champ = false;
}

champ_t *add_champ(champ_t **champ, char *brut_name, utils_parser_t *up)
{
    champ_t *tmp = PMALLOC(tmp, sizeof(champ_t));
    static int last_address = 0;
    static int nb = 0;
    static int nb_prog = 0;

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