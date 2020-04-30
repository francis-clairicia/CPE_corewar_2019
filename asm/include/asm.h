/*
** EPITECH PROJECT, 2020
** asm
** File description:
** ASM_H_
*/

#ifndef ASM_H_
#define ASM_H_

#include <stdbool.h>
#include <stdio.h>
#include "op.h"

#define REVERSED_NB(nb) (nb & 0x000000FFU) << 24 | (nb & 0x0000FF00U) << 8 | \
    (nb & 0x00FF0000U) >> 8 | (nb & 0xFF000000U) >> 24

int assembly(char const *file);

char **read_file(char const *file);
void remove_comments(char **array);
bool setup_header(char **array, header_t *header);
void print_number(int nb, FILE *file);

#endif /* !ASM_H_ */
