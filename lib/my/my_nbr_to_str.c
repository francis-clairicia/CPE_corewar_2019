/*
** EPITECH PROJECT, 2019
** my_nbr_to_str
** File description:
** Put a number into a string
*/

#include <stdlib.h>

int my_nbr_len(long nb);

char *my_revstr(char const *str);

static void get_nbr(char *str, int nb)
{
    int sign = 0;
    int i = 0;

    if (nb < 0) {
        sign = 1;
        nb = -nb;
    }
    while (nb != 0) {
        str[i] = (nb % 10) + 48;
        nb /= 10;
        i += 1;
    }
    if (sign == 1) {
        str[i] = '-';
        i += 1;
    }
    str[i] = '\0';
    my_revstr(str);
}

char *my_nbr_to_str(int nb)
{
    int len = my_nbr_len(nb);
    char *str = malloc(sizeof(char) * (len + 1));

    if (str == NULL)
        return (NULL);
    if (nb == 0) {
        str[0] = '0';
        str[1] = '\0';
    } else {
        get_nbr(str, nb);
    }
    return (str);
}
