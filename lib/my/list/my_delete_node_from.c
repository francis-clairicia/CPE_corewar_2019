/*
** EPITECH PROJECT, 2019
** My_Lib_C
** File description:
** my_delete_node_from.c
*/

#include "mylist.h"

void _delete_node_from_data(list_t *list, const void *data, size_t size,
    void (*free_func)())
{
    node_t *node = NULL;

    if (list == NULL)
        return;
    node = _node_from_data(*list, data, size);
    if (node == NULL)
        return;
    my_delete_node(list, node->index, free_func);
}

void my_delete_node_from_node(list_t *list, node_t *node, void (*free_func)())
{
    if (list == NULL || !my_find_node(*list, node))
        return;
    my_delete_node(list, node->index, free_func);
}