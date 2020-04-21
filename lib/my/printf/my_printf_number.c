/*
** EPITECH PROJECT, 2019
** my_printf
** File description:
** Recode the print function
*/

#include "my_printf.h"

int print_number(va_list args, modifier_t *infos)
{
    long nb = va_arg(args, long);
    char *l_mod = infos->length_modifier;

    if (my_strcmp(l_mod, "ll") == 0 || my_strcmp(l_mod, "l") == 0
        || my_strcmp(l_mod, "q") == 0)
        return (my_putnbr_long((long)nb, infos));
    if (my_strcmp(l_mod, "h") == 0)
        return (my_putnbr_long((short)nb, infos));
    if (my_strcmp(l_mod, "hh") == 0)
        return (my_putnbr_long((char)nb, infos));
    return (my_putnbr_long((int)nb, infos));
}
