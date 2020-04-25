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

#define PMALLOC(var, size)  \
malloc(size);               \
if (!var)                   \
    return NULL;

#define IMALLOC(var, size)  \
malloc(size);               \
if (!var)                   \
    return 84;

#define PREALLOC(var, size) \
realloc(var, size);         \
if (!var)                   \
    return NULL;

#define IREALLOC(var, size) \
realloc(var, size);         \
if (!var)                   \
    return 84;

#endif