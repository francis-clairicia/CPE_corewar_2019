/*
** EPITECH PROJECT, 2019
** asm
** File description:
** print_error.c
*/

#include "my.h"
#include "my_errno.h"

static const char * const error_messages[] = {
    [E_SUCCESS] = NULL,
    [E_INTERNAL_ERROR] = "Internal error",
    [E_INVALID_SYNTAX] = "Syntax invalid",
    [E_INVALID_INSTRUCTION] = "Invalid instruction",
    [E_INVALID_ARG] = "The argument given to the instruction is invalid",
    [E_INVALID_REGISTER] = "Invalid register number",
    [E_INVALID_LABEL] = "Invalid label name",
    [E_MULTIPLE_LABEL_DEFINITION] = "Multiple definition of the same label",
    [E_UNDEFINED_LABEL] = "Undefined label"
};

static char const *get_filename(char const *file)
{
    int slash = 0;

    while ((slash = my_strchr_index(file, '/')) >= 0)
        file = &file[slash + 1];
    return (file);
}

void print_error(char const *file, int line)
{
    char const *message = error_messages[my_errno];
    char const *filename = get_filename(file);
    char format[] = "\033[1;37masm, %s, line %d: \033[1;31m%s.\n\033[0m";

    if (my_errno == E_SUCCESS)
        return;
    my_dprintf(2, format, filename, line, message);
}