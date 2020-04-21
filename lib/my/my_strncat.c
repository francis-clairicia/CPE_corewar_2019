/*
** EPITECH PROJECT, 2019
** Mystrncat
** File description:
** Append string into another
*/

#include <stddef.h>

int my_strlen(char const *str);

char *my_strncat(char *dest, char const *src, int n)
{
    int i = 0;
    int len = my_strlen(dest);

    if (dest == NULL)
        return (NULL);
    if (src == NULL)
        return (dest);
    while ((i < n) && (src[i] != '\0')) {
        dest[len + i] = src[i];
        i += 1;
    }
    dest[len + i] = '\0';
    return (dest);
}
