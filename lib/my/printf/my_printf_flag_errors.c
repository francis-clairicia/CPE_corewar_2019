/*
** EPITECH PROJECT, 2019
** PSU_my_printf_2019
** File description:
** my_printf_flag_errors.c
*/

#include "my_printf.h"

static int check_precision(char const *mod, char flag)
{
    int i = my_strchr_index(mod, flag);

    if (i == -1)
        return (0);
    if (flag == '-' && my_getnbr(mod) > 0)
        return (1);
    if (my_strchr_index("123456789", mod[i + 1]) == -1)
        return (1);
    return (0);
}

int non_valid_flags(char const *mod)
{
    if (check_precision(mod, '-') == 1)
        return (1);
    if (check_precision(mod, '.') == 1)
        return (1);
    return (0);
}