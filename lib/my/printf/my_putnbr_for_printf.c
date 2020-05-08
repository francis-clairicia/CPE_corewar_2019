/*
** EPITECH PROJECT, 2019
** my_printf
** File description:
** Base conversion
*/

#include "my_printf.h"

static long abs_nb(long nb)
{
    if (nb < 0)
        return (-nb);
    return (nb);
}

int my_putnbr_base_u(unsigned long nb, modifier_t *infos, char const *base)
{
    char *nb_converted = convert_to_base_u(nb, base);
    int size = my_strlen(nb_converted);
    int len = size;

    infos->sharp = (infos->sharp == 1 && nb > 0);
    len += print_before(infos, size);
    my_putstr_fd(infos->fd, nb_converted);
    len += print_after(infos, size);
    free(nb_converted);
    return (len);
}

int my_putnbr_long(long nb, modifier_t *infos)
{
    char *nb_converted = convert_to_base_long(abs_nb(nb), "0123456789");
    int size = my_strlen(nb_converted);
    int len = size;

    infos->sharp = (infos->sharp == 1 && nb > 0);
    infos->sign = ((infos->sign == 1 && nb != 0) || nb < 0);
    if (infos->sign == 1)
        infos->sign = (nb >= 0) ? '+' : '-';
    len += print_before(infos, size);
    my_putstr_fd(infos->fd, nb_converted);
    len += print_after(infos, size);
    free(nb_converted);
    return (len);
}
