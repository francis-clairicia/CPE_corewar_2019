/*
** EPITECH PROJECT, 2019
** my_strncpy.c
** File description:
** Copy n characters from a string into an another
*/

#include <stddef.h>

char *my_strncpy(char *dest, char const *src, int n)
{
    int i = 0;

    if (dest == NULL)
        return (NULL);
    if (src == NULL)
        return (dest);
    while ((i < n) && (src[i] != '\0')) {
        dest[i] = src[i];
        i += 1;
    }
    while (i < n + 1) {
        dest[i] = '\0';
        i += 1;
    }
    return (dest);
}
