/*
** EPITECH PROJECT, 2019
** my_free_list
** File description:
** Free data in list
*/

#include "mylist.h"

void my_free_list(list_t **list, void (*free_function)())
{
    list_t *element;

    while ((*list) != NULL) {
        element = *list;
        *list = (*list)->next;
        if (free_function != NULL && (void *)(element->data) != NULL)
            free_function((void *)(element->data));
        free(element);
    }
}
