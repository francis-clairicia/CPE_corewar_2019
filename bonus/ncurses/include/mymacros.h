/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** mymacros.h
*/

#ifndef MYMACROS_H
#define MYMACROS_H

#include <stdlib.h>
#include <unistd.h>
#include "my.h"

#define PMALLOC(var, size)              \
malloc(size);                           \
if (!var) {                             \
    my_putstr_fd(2, "Malloc error.\n"); \
    return NULL;                        \
}

#define IMALLOC(var, size)              \
malloc(size);                           \
if (!var) {                             \
    my_putstr_fd(2, "Malloc error.\n"); \
    return 84;                          \
}

#define ICHECK(var)     \
if (!var)               \
    return 84;

#define PCHECK(var)     \
if (!var)               \
    return NULL;

#define IRETURN(var)    \
if (var == 84)          \
    return 84;

#endif