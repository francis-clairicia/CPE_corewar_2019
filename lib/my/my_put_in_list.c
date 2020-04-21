/*
** EPITECH PROJECT, 2019
** my_put_in_list
** File description:
** Put an element into a list
*/

#include "mylist.h"

int my_put_in_list(list_t **list, long data)
{
    list_t *element = malloc(sizeof(list_t));

    if (element == NULL)
        return (0);
    element->data = data;
    element->next = *list;
    if (*list == NULL)
        element->previous = element;
    else
        element->previous = (*list)->previous;
    *list = element;
    return (1);
}
