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
        if (champ->parent)
            free(champ->header);
        if (champ->children)
            free_champ(champ->children);
        tmp = champ->next;
        champ->next = NULL;
        free(champ);
    }
}