/*
** EPITECH PROJECT, 2019
** My str_isupper()
** File description:
** test if a string has only uppercase alphabethical character
*/

#include <stddef.h>

int my_str_isupper(char const *str)
{
    int i = 0;

    if (str == NULL)
        return (0);
    while (str[i] != '\0') {
        if ((str[i] < 'A') || (str[i] > 'Z'))
            return (0);
        i += 1;
    }
    return (1);
}
