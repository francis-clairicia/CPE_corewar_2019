/*
** EPITECH PROJECT, 2019
** asm
** File description:
** valid_label.c
*/

#include "asm.h"
#include "my.h"

bool valid_label(char const *label, errno_t *errno)
{
    if (label == NULL)
        return (true);
    if (label[0] == '\0')
        return (set_errno(errno, E_INVALID_LABEL));
    if (!my_str_contains_only(label, LABEL_CHARS))
        return (set_errno(errno, E_INVALID_LABEL));
    return (true);
}