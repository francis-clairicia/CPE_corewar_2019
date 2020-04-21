/*
** EPITECH PROJECT, 2019
** My str_islower()
** File description:
** test if a string has only lowercase alphabethical character
*/

#include <stddef.h>

int my_str_islower(char const *str)
{
    int i = 0;

    if (str == NULL)
        return (0);
    while (str[i] != '\0') {
        if ((str[i] < 'a') || (str[i] > 'z'))
            return (0);
        i += 1;
    }
    return (1);
}
