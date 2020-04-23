/*
** EPITECH PROJECT, 2019
** my_put_in_list
** File description:
** Put an element into a list
*/

#include "mylist.h"

static void increase_index(node_t *node)
{
    while (node != NULL) {
        node->index += 1;
        node = node->next;
    }
}

static int put_node_as_start(list_t *list, const void *data, size_t size)
{
    node_t *element = _create_node(data, size);

    if (element == NULL)
        return (0);
    element->next = list->start;
    if (list->size == 0)
        list->end = element;
    else
        list->start->previous = element;
    list->start = element;
    list->size += 1;
    increase_index(list->start->next);
    return (1);
}

static int put_node_as_end(list_t *list, const void *data, size_t size)
{
    node_t *element = _create_node(data, size);

    if (element == NULL)
        return (0);
    if (list->size == 0) {
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

static int put_node_at_index(list_t *list, const void *data,
    size_t size, size_t index)
{
    node_t *node_index = list->start;
    node_t *element = _create_node(data, size);

    if (element == NULL)
        return (0);
    while (node_index->index != index)
        node_index = node_index->next;
    node_index->previous->next = element;
    element->previous = node_index->previous;
    element->next = node_index;
    element->index = node_index->index;
    node_index->previous = element;
    increase_index(node_index);
    list->size += 1;
    return (1);
}

int _insert_in_list(list_t *list, const void *data, size_t size, int index)
{
    size_t idx = 0;

    if (list == NULL)
        return (0);
    if (index >= 0) {
        if (index == 0)
            return (put_node_as_start(list, data, size));
        if ((size_t)index >= list->size)
            return (put_node_as_end(list, data, size));
    } else {
        if (index == -1)
            return (put_node_as_end(list, data, size));
        if ((int)(list->size + index) <= 0)
            return (put_node_as_start(list, data, size));
    }
    idx = (index < 0) ? list->size + 1 + index : (size_t)index;
    return (put_node_at_index(list, data, size, idx));
}
