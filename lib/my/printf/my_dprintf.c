/*
** EPITECH PROJECT, 2019
** My_Lib_C
** File description:
** my_dprintf.c
*/

#include "my_printf.h"

int my_dprintf(int fd, char const *format, ...)
{
    va_list args;
    int nb_print = 0;
    int save_stdout = 0;

    if (fd < 0)
        return (-1);
    save_stdout = dup(STDOUT_FILENO);
    dup2(fd, STDOUT_FILENO);
    va_start(args, format);
    nb_print = my_vprintf(format, args);
    va_end(args);
    dup2(save_stdout, STDOUT_FILENO);
    return (nb_print);
}