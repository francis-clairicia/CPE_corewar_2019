/*
** EPITECH PROJECT, 2019
** My get nbr
** File description:
** Get a number in a string
*/

#include <stddef.h>

int my_strlen(char const *str);

static int index_of_first_digit(char const *str)
{
    int i = 0;
    int len = my_strlen(str);

    while (i < len) {
        if (str[i] >= '0' && str[i] <= '9')
            return (i);
        i += 1;
    }
    return (0);
}

int negative_nb(char const *str, int index_first)
{
    int number_of_minus = 0;
    int i = index_first - 1;

    while (i >= 0 && (str[i] == '-' || str[i] == '+')) {
        if (str[i] == '-')
            number_of_minus += 1;
        i -= 1;
    }
    return (number_of_minus % 2);
}

int my_getnbr(char const *str)
{
    long nb = 0;
    int result = 0;
    int i = index_of_first_digit(str);
    int sign = negative_nb(str, i);

    if (str == NULL)
        return (0);
    while (str[i] >= '0' && str[i] <= '9') {
        nb = (nb * 10) + (str[i] - 48);
        if (nb > (2147483647L + sign))
            return (0);
        i += 1;
    }
    result = nb;
    return ((sign == 1) ? result * (-1) : result);
}
