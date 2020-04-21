/*
** EPITECH PROJECT, 2019
** My put nbr base
** File description:
** Base
*/

#include <stdlib.h>

int my_putstr(char const *str);

char *convert_to_base(int nbr, char const *base);

int my_putnbr_base(int nbr, char const *base)
{
    char *nbr_converted = convert_to_base(nbr, base);

    my_putstr(nbr_converted);
    free(nbr_converted);
    return (0);
}
