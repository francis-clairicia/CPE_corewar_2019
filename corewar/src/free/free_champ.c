/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** free_champ.c
*/

#include "corewar.h"
#include "stdlib.h"

void free_champ(champ_t *champ)
{
    champ_t *tmp = champ;

    for (; champ; champ = tmp) {
        fclose(champ->fp);
        free(champ->header);
        free(champ->op->mnemonique);
        free(champ->op->comment);
        free(champ->op);
        free(champ->reg);
        free(champ->brut_name);
        tmp = tmp->next;
        free(champ);
    }
}