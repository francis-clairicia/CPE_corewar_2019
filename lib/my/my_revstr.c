/*
** EPITECH PROJECT, 2019
** my_revstr.c
** File description:
** Reverse the string
*/

#include <stddef.h>

int my_strlen(char const *str);

char *my_revstr(char *str)
{
    char c;
    int i = 0;
    int j = my_strlen(str) - 1;

    if (str == NULL)
        return (NULL);
    while (i < j) {
        c = str[i];
        str[i] = str[j];
        str[j] = c;
        i += 1;
        j -= 1;
    }
    return (str);
}
