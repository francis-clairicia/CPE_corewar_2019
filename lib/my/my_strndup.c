/*
** EPITECH PROJECT, 2019
** My_Lib_C
** File description:
** my_strndup.c
*/

#include <stdlib.h>

char *my_strncpy(char *dest, char const *src, int n);

int my_strlen(char const *str);

char *my_strndup(char const *src, int n)
{
    int len = my_strlen(src);
    char *dest;

    if (src == NULL)
        return (NULL);
    if (n > len)
        n = len;
    dest = malloc(sizeof(char) * (n + 1));
    if (dest == NULL)
        return (NULL);
    my_strncpy(dest, src, n);
    return (dest);
}