/*
** EPITECH PROJECT, 2019
** my_nbr_len
** File description:
** length of a number
*/

#include "my_printf.h"

int my_nbr_len_u(unsigned long nb)
{
    int len = 1;

    while (nb > 9) {
        nb /= 10;
        len += 1;
    }
    return (len);
}
