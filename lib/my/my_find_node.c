/*
** EPITECH PROJECT, 2019
** My_Lib_C
** File description:
** my_find_node.c
*/

#include "mylist.h"

list_t *my_find_node(list_t *list, list_t *node_to_find, int *index)
{
    int i = 0;
    list_t *node = NULL;

    for (node = list; node != NULL && node != node_to_find; node = node->next)
        i += 1;
    if (index != NULL && node != NULL)
        *index = i;
    return (node);
}