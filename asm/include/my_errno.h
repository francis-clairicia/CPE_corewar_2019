/*
** EPITECH PROJECT, 2019
** asm
** File description:
** my_errno.h
*/

#ifndef ASM_ERRNO_H_
#define ASM_ERRNO_H_

#include <stdbool.h>

typedef enum MY_ERRNO_VALUES
{
    E_SUCCESS,
    E_INTERNAL_ERROR,
    E_INVALID_SYNTAX,
    E_INVALID_INSTRUCTION,
    E_INVALID_ARG,
    E_INVALID_REGISTER,
    E_INVALID_LABEL,
    E_MULTIPLE_LABEL_DEFINITION,
    E_UNDEFINED_LABEL
} errno_t;

extern errno_t my_errno;

static inline bool set_errno(errno_t value)
{
    my_errno = value;
    return (my_errno == E_SUCCESS);
}

#endif