/*
** EPITECH PROJECT, 2019
** My_Lib_C
** File description:
** my_array_contains.c
*/

#include <stddef.h>

int my_strcmp(char const *s1, char const *s2);

int my_array_contains(char * const *array, char const *to_find)
{
    int i = 0;

    if (array == NULL || to_find == NULL)
        return (0);
    for (i = 0; array[i] != NULL; i += 1) {
        if (my_strcmp(array[i], to_find) == 0)
            return (1);
    }
    return (0);
}