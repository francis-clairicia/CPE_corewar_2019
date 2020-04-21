/*
** EPITECH PROJECT, 2019
** My strupcase()
** File description:
** Put letter in uppercase
*/

#include <stddef.h>

char *my_strupcase(char *str)
{
    int i = 0;

    if (str == NULL)
        return (NULL);
    while (str[i] != '\0') {
        if ((str[i] >= 'a') && (str[i] <= 'z'))
            str[i] -= 32;
        i += 1;
    }
    return (str);
}
