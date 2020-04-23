/*
** EPITECH PROJECT, 2019
** My_Lib_C
** File description:
** my_create_node.c
*/

#include <stdio.h>
#include "mylist.h"

static int copy_data(void *dest, void const *src, size_t n)
{
    size_t i = 0;

    if (dest == NULL || src == NULL)
        return (0);
    for (i = 0; i < n; i += 1)
        ((char *)dest)[i] = ((char const *)src)[i];
    return (1);
}

node_t *_create_node(const void *data, size_t size)
{
    node_t *element = malloc(sizeof(node_t));

    if (element != NULL) {
        element->index = 0;
        element->next = NULL;
        element->previous = NULL;
        element->data.ptr = malloc(size);
        element->data.size = size;
        if (!copy_data(element->data.ptr, data, size)) {
            free(element->data.ptr);
            free(element);
            return (NULL);
        }
    }
    return (element);
}