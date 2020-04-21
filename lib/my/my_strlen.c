/*
** EPITECH PROJECT, 2019
** My str len
** File description:
** Find the lenght of a string
*/

#include <stddef.h>

int my_strlen(char const *str)
{
    int i = 0;

    if (str == NULL)
        return (0);
    while (str[i] != '\0') {
        i += 1;
    }
    return (i);
}
