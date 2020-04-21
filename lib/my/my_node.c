/*
** EPITECH PROJECT, 2019
** My_Lib_C
** File description:
** my_node.c
*/

#include "mylist.h"

static list_t *search_node_by_beginning(list_t *begin, int index)
{
    int i = 0;

    while (begin != NULL) {
        if (i == index)
            return (begin);
        begin = begin->next;
        i += 1;
    }
    return (NULL);
}

static list_t *search_node_by_end(list_t *last, int index)
{
    int i = -1;

    while (last->next != NULL || i == -1) {
        if (i == index)
            return (last);
        last = last->previous;
    }
    return (NULL);
}

list_t *my_node(list_t *begin, int index)
{
    if (begin == NULL)
        return (NULL);
    if (index < 0)
        return (search_node_by_end(begin->previous, index));
    return (search_node_by_beginning(begin, index));
}

list_t *my_node_from_data(list_t *begin, long data, int *index)
{
    int i = 0;
    list_t *node = NULL;

    if (begin == NULL)
        return (NULL);
    for (node = begin; node != NULL && node->data != data; node = node->next)
        i += 1;
    if (index != NULL && node != NULL)
        *index = i;
    return (node);
}