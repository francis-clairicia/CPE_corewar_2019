/*
** EPITECH PROJECT, 2019
** asm
** File description:
** valid_instruction.c
*/

#include "asm.h"
#include "my.h"

bool valid_instruction(char const *mnemonique, int *instruction, errno_t *err)
{
    int len = 0;

    if (!mnemonique || !instruction)
        return (set_errno(err, E_INTERNAL_ERROR));
    len = my_strlen(mnemonique);
    if (len == 0)
        return (set_errno(err, E_INVALID_INSTRUCTION));
    for (register int i = 0; op_tab[i].mnemonique != NULL; i += 1) {
        if (my_strncmp(mnemonique, op_tab[i].mnemonique, len) == 0) {
            *instruction = i;
            return (true);
        }
    }
    return (set_errno(err, E_INVALID_INSTRUCTION));
}