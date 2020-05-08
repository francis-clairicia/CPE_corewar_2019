/*
** EPITECH PROJECT, 2019
** asm
** File description:
** valid_instruction.c
*/

#include "asm.h"
#include "my.h"

bool valid_instruction(char const *mnemonic, int *instruction, errno_t *err)
{
    int len = 0;

    if (!mnemonic || !instruction)
        return (set_errno(err, E_INTERNAL_ERROR));
    len = my_strlen(mnemonic);
    if (len == 0)
        return (set_errno(err, E_INVALID_INSTRUCTION));
    for (register int i = 0; op_tab[i].mnemonic != NULL; i += 1) {
        if (my_strncmp(mnemonic, op_tab[i].mnemonic, len) == 0) {
            *instruction = i;
            return (true);
        }
    }
    return (set_errno(err, E_INVALID_INSTRUCTION));
}