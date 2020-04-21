/*
** EPITECH PROJECT, 2019
** My str_isprintable()
** File description:
** test if a string has only printable character
*/

#include <stddef.h>

int my_str_isprintable(char const *str)
{
    int i = 0;

    if (str == NULL)
        return (0);
    while (str[i] != '\0') {
        if (str[i] < 32)
            return (0);
        i += 1;
    }
    return (1);
}
