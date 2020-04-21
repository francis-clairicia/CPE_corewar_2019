/*
** EPITECH PROJECT, 2019
** my_strstr.c
** File description:
** Find a string into an another
*/

#include <stddef.h>

char *my_strncmp(char const  *s1, char const *s2, int n);

int my_strlen(char const *str);

char *my_strstr(char *str, char const *to_find)
{
    int i = 0;
    int len_str_to_find = my_strlen(to_find);

    if (str == NULL || to_find == NULL || my_strlen(str) < len_str_to_find)
        return (NULL);
    while (str[i + len_str_to_find - 1] != '\0') {
        if (my_strncmp(&str[i], to_find, len_str_to_find) == 0)
            return (&str[i]);
        i += 1;
    }
    return (NULL);
}

int my_strstr_index(char const *str, char const *to_find)
{
    int i = 0;
    int len_str_to_find = my_strlen(to_find);

    if (str == NULL || to_find == NULL || my_strlen(str) < len_str_to_find)
        return (-1);
    while (str[i + len_str_to_find - 1] != '\0') {
        if (my_strncmp(&str[i], to_find, len_str_to_find) == 0)
            return (i);
        i += 1;
    }
    return (-1);
}