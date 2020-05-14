/*
** EPITECH PROJECT, 2019
** My_Lib_C
** File description:
** my_node_from.c
*/

#include <stdio.h>
#include "mylist.h"

static int compare_data(data_node_t node_data, const void *data, size_t size)
{
    const char *first_ptr = NULL;
    const char *second_ptr = NULL;
    size_t i = 0;

    if (node_data.size != size)
        return (0);
    first_ptr = node_data.ptr;
    second_ptr = data;
    for (i = 0; i < node_data.size; i += 1) {
        if (first_ptr[i] != second_ptr[i])
            return (0);
    }
    return (1);
}

node_t *node_from_data(list_t list, const void *data, size_t size)
{
    node_t *node = NULL;

    for (node = list.start; node != NULL; node = node->next) {
        if (compare_data(node->data, data, size) == 1)
            break;
    }
    return (node);
}