/*
** EPITECH PROJECT, 2019
** My_Lib_C
** File description:
** my_node.c
*/

#include "mylist.h"

node_t *my_node(list_t list, int index)
{
    node_t *node = NULL;
    size_t index_to_find = (index >= 0) ? (size_t)index : list.size + index;

    for (node = list.start; node != NULL; node = node->next) {
        if (node->index == index_to_find)
            return (node);
    }
    return (NULL);
}