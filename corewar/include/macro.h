/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** macro.h
*/

#ifndef MACRO_H
#define MACRO_H

#include <stdlib.h>
#include <unistd.h>

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

#define PREALLOC(var, size)                 \
realloc(var, size);                         \
if (!var) {                                 \
    my_putstr_fd(2, "Realloc error.\n");    \
    return NULL;                            \
}

#define IREALLOC(var, size)                 \
realloc(var, size);                         \
if (!var) {                                 \
    my_putstr_fd(2, "Realloc error.\n");    \
    return 84;                              \
}

#define ICHECK(var)     \
if (!var)               \
    return 84;

#define PCHECK(var)     \
if (!var)               \
    return NULL;

#endif