/*
** EPITECH PROJECT, 2019
** Mystrcat
** File description:
** Append string into another
*/

#include <stddef.h>

int my_strlen(char const *str);

char *my_strcat(char *dest, char const *src)
{
    int i = 0;
    int len = my_strlen(dest);

    if (src == NULL)
        return (dest);
    if (dest == NULL)
        return (NULL);
    while (src[i] != '\0') {
        dest[len + i] = src[i];
        i += 1;
    }
    dest[len + i] = '\0';
    return (dest);
}
