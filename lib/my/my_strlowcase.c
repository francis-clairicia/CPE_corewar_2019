/*
** EPITECH PROJECT, 2019
** My strlowcase()
** File description:
** Put letter in uppercase
*/

#include <stddef.h>

char *my_strlowcase(char *str)
{
    int i = 0;

    if (str == NULL)
        return (NULL);
    while (str[i] != '\0') {
        if ((str[i] >= 'A') && (str[i] <= 'Z'))
            str[i] += 32;
        i += 1;
    }
    return (str);
}
