/*
** EPITECH PROJECT, 2019
** my_printf
** File description:
** print command-like
*/

#include "my_printf.h"

int print_pointer(va_list args, modifier_t *infos)
{
    unsigned long nb = va_arg(args, unsigned long);
    int len = 0;

    len += print_before(infos, my_nbr_len_u(nb));
    if (nb > 0)
        len += my_dprintf(infos->fd, "%#lx", nb);
    else {
        my_putstr_fd(infos->fd, "(nil)");
        len += 5;
    }
    len += print_after(infos, my_nbr_len_u(nb));
    return (len);
}
