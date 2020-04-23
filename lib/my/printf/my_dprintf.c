/*
** EPITECH PROJECT, 2019
** My_Lib_C
** File description:
** my_dprintf.c
*/

#include "my_printf.h"

int my_vdprintf(int fd, char const *format, va_list ap)
{
    int save_stdout = 0;
    int nb_print = 0;

    if (fd < 0)
        return (-1);
    save_stdout = dup(STDOUT_FILENO);
    dup2(fd, STDOUT_FILENO);
    nb_print = my_vprintf(format, ap);
    dup2(save_stdout, STDOUT_FILENO);
    return (nb_print);
}

int my_dprintf(int fd, char const *format, ...)
{
    va_list ap;
    int nb_print = 0;

    if (fd < 0)
        return (-1);
    va_start(ap, format);
    nb_print = my_vdprintf(fd, format, ap);
    va_end(ap);
    return (nb_print);
}