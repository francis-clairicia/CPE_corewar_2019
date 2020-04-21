/*
** EPITECH PROJECT, 2019
** My_Lib_C
** File description:
** my_str_isalphanum.c
*/

#include <stddef.h>

int char_is_alphanum(char c)
{
    if (c >= 'a' && c <= 'z')
        return (1);
    if (c >= 'A' && c <= 'Z')
        return (1);
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}

int my_str_isalphanum(char const *str)
{
    int i = 0;

    if (str == NULL)
        return (0);
    while (str[i] != '\0') {
        if (!char_is_alphanum(str[i]))
            return (0);
        i += 1;
    }
    return (1);
}