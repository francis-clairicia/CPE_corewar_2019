/*
** EPITECH PROJECT, 2019
** my_put_in_list
** File description:
** Put an element into a list
*/

#include "mylist.h"

static int put_node_as_start(list_t *list, node_t *element)
{
    node_t *node = NULL;

    if (element == NULL)
        return (0);
    element->previous = NULL;
    element->index = 0;
    element->next = list->start;
    if (list->size == 0)
        list->end = element;
    else
        list->start->previous = element;
    list->start = element;
    list->size += 1;
    for (node = list->start->next; node != NULL; node = node->next)
        node->index += 1;
    return (1);
}

static int put_node_as_end(list_t *list, node_t *element)
{
    if (element == NULL)
        return (0);
    element->previous = NULL;
    element->next = NULL;
    if (list->size == 0) {
        element->index = 0;
        list->start = element;
    } else {
        element->index = list->end->index + 1;
        list->end->next = element;
        element->previous = list->end;
    }
    list->end = element;
    list->size += 1;
    return (1);
}

static int put_node_at_index(list_t *list, node_t *element, size_t index)
{
    node_t *node_index = list->start;

    if (element == NULL)
        return (0);
    while (node_index->index != index)
        node_index = node_index->next;
    node_index->previous->next = element;
    element->previous = node_index->previous;
    element->next = node_index;
    element->index = node_index->index;
    node_index->previous = element;
    for (; node_index != NULL; node_index = node_index->next)
        node_index->index += 1;
    list->size += 1;
    return (1);
}

int my_insert_node(list_t *list, node_t *node, int index, int copy)
{
    size_t idx = 0;
    node_t *node_to_add = node;

    if (list == NULL || node == NULL)
        return (0);
    if (copy != 0)
        node_to_add = create_node(node->data.ptr, node->data.size);
    if (index >= 0) {
        if (index == 0)
            return (put_node_as_start(list, node_to_add));
        if ((size_t)index >= list->size)
            return (put_node_as_end(list, node_to_add));
    } else {
        if (index == -1)
            return (put_node_as_end(list, node_to_add));
        if ((int)(list->size + index) <= 0)
            return (put_node_as_start(list, node_to_add));
    }
    idx = (index < 0) ? list->size + 1 + index : (size_t)index;
    return (put_node_at_index(list, node_to_add, idx));
}
