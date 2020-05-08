/*
** EPITECH PROJECT, 2019
** My_Lib_C
** File description:
** my_printf.c
*/

#include "my_printf.h"

int my_vprintf(char const *format, va_list ap)
{
    return (my_vdprintf(1, format, ap));
}

int my_printf(char const *format, ...)
{
    va_list args;
    int nb_print = 0;

    va_start(args, format);
    nb_print = my_vprintf(format, args);
    va_end(args);
    return (nb_print);
}