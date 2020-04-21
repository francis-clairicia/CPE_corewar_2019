/*
** EPITECH PROJECT, 2019
** My_Lib_C
** File description:
** my_show_word_array.c
*/

#include <stddef.h>

int my_putstr(char const *str);

void my_show_word_array(char * const *array)
{
    int i = 0;

    while (array != NULL && array[i] != NULL) {
        my_putstr(array[i]);
        my_putstr("\n");
        i += 1;
    }
}