/*
** EPITECH PROJECT, 2019
** my_strchr_index
** File description:
** Find a char into a string
*/

#include <stddef.h>

char *my_strchr(char *str, int c)
{
    int i = 0;

    if (str == NULL)
        return (NULL);
    while (str[i] != '\0') {
        if (str[i] == c)
            return (&str[i]);
        i += 1;
    }
    return (NULL);
}

int my_strchr_index(char const *str, int c)
{
    int i = 0;

    if (str == NULL)
        return (-1);
    while (str[i] != '\0') {
        if (str[i] == c)
            return (i);
        i += 1;
    }
    return (-1);
}
