/*
** EPITECH PROJECT, 2019
** My str_isnum()
** File description:
** test if a string has only digits character
*/

#include <stddef.h>

int my_str_isnum(char const *str)
{
    int i = 0;

    if (str == NULL)
        return (0);
    if (str[0] == '-') {
        if (str[1] == '\0')
            return (0);
        i = 1;
    }
    while (str[i] != '\0') {
        if ((str[i] < '0') || (str[i] > '9'))
            return (0);
        i += 1;
    }
    return (1);
}
