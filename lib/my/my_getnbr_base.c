/*
** EPITECH PROJECT, 2019
** My get nbr base
** File description:
** Get a number in a string
*/

#include <stddef.h>

int my_strchr_index(char const *str, char c);

int my_strlen(char const *str);

int negative_nb(char const *str, int index_first);

static int index_of_first_digit_base(char const *str, char const *base)
{
    int i = 0;
    int len = my_strlen(str);

    while (i < len) {
        if (my_strchr_index(base, str[i]) != -1)
            return (i);
        i += 1;
    }
    return (0);
}

int my_getnbr_base(char const *str, char const *base)
{
    int nb = 0;
    int digit = 0;
    int i = index_of_first_digit_base(str, base);
    int sign = negative_nb(str, i);
    int nb_base = my_strlen(base);

    if (str == NULL || base == NULL)
        return (0);
    while (my_strchr_index(base, str[i]) != -1) {
        digit = my_strchr_index(base, str[i]);
        if (sign == 0 && (nb <= (2147483647 - digit) / nb_base))
            nb = (nb * nb_base) + digit;
        else if (sign == 1 && (nb >= (-2147483648 + digit) / nb_base))
            nb = (nb * nb_base) - digit;
        else
            return (0);
        i += 1;
    }
    return (nb);
}
