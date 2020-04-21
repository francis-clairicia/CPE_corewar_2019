/*
** EPITECH PROJECT, 2019
** My_Lib_C
** File description:
** my_str_contains_only.c
*/

#include <stddef.h>

int my_strchr_index(char const *str, int c);

int my_str_contains_only(char const *str, char const *valid)
{
    int i = 0;

    if (str == NULL)
        return (0);
    if (valid == NULL || valid[0] == '\0')
        return (1);
    for (i = 0; str[i] != '\0'; i += 1) {
        if (my_strchr_index(valid, str[i]) == -1)
            return (0);
    }
    return (1);
}