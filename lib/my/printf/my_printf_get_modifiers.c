/*
** EPITECH PROJECT, 2019
** PSU_my_printf_2019
** File description:
** my_printf_get_modifiers.c
*/

#include "my_printf.h"

char *get_modifiers(int *i, char const *str)
{
    char *modifiers = NULL;
    int j = 0;

    while (str[j] != '\0' && my_strchr_index("%dibouxXcsSp", str[j]) == -1) {
        if (my_strchr_index("lhq#0123456789+- .", str[j]) == -1)
            return (NULL);
        j += 1;
    }
    modifiers = malloc(sizeof(char) * (j + 1));
    my_strncpy(modifiers, str, j);
    modifiers[j] = 0;
    *i += j;
    return (modifiers);
}