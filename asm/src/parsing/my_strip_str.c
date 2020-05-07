/*
** EPITECH PROJECT, 2019
** asm
** File description:
** my_strip_str.c
*/

#include "my.h"

static void remove_at_the_begin(char *str, char const characters[])
{
    int i = 0;

    while (my_strchr_index(characters, str[0]) >= 0) {
        for (i = 0; str[i] != '\0'; i += 1) {
            str[i] = str[i + 1];
        }
    }
}

static void remove_at_the_end(char *str, char const characters[])
{
    int i = my_strlen(str) - 1;

    while (my_strchr_index(characters, str[i]) >= 0) {
        str[i] = '\0';
        i -= 1;
    }
}

char *my_strip_str(char *str, char const characters[])
{
    if (str != NULL && characters != NULL) {
        remove_at_the_begin(str, characters);
        remove_at_the_end(str, characters);
    }
    return (str);
}