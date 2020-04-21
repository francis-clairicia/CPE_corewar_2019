/*
** EPITECH PROJECT, 2019
** My_Lib_C
** File description:
** my_list.c
*/

#include <stdarg.h>
#include "mylist.h"

list_t *my_list(int nb_element, ...)
{
    va_list ap;
    list_t *list = NULL;
    int i = 0;

    va_start(ap, nb_element);
    while (i < nb_element) {
        my_append_to_list(&list, va_arg(ap, long));
        i += 1;
    }
    va_end(ap);
    return (list);
}