/*
** EPITECH PROJECT, 2019
** my_strncmp.c
** File description:
** Compare the n first character of two strings
*/

#include <stddef.h>

int my_strcmp(char const *s1, char const *s2);

int my_strlen(char const *str);

char *my_strncpy(char *dest, char const *src, int n);

int my_strncmp(char const *s1, char const *s2, int n)
{
    char s1_cut[n + 1];

    if (s1 == NULL || s2 == NULL)
        return (my_strcmp(s1, s2));
    if (n >= my_strlen(s1))
        return (my_strcmp(s1, s2));
    return (my_strcmp(my_strncpy(s1_cut, s1, n), s2));
}
