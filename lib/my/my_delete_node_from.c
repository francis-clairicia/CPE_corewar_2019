/*
** EPITECH PROJECT, 2019
** My_Lib_C
** File description:
** my_delete_node_from.c
*/

#include "mylist.h"

void my_delete_node_from_data(list_t **list, long data, void (*free_func)())
{
    int index = 0;
    list_t *node = NULL;

    if (list == NULL)
        return;
    node = my_node_from_data(*list, data, &index);
    if (node == NULL)
        return;
    my_delete_node(list, index, free_func);
}

void my_delete_node_from_node(list_t **list, list_t *node, void (*free_func)())
{
    int index = 0;
    list_t *node_found = NULL;

    if (list == NULL)
        return;
    node_found = my_find_node(*list, node, &index);
    if (node_found == NULL)
        return;
    my_delete_node(list, index, free_func);
}