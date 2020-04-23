/*
** EPITECH PROJECT, 2019
** My_Lib_C
** File description:
** my_find_node.c
*/

#include "mylist.h"

int my_find_node(list_t list, const node_t *to_find)
{
    node_t *node = NULL;

    for (node = list.start; node != NULL && node != to_find; node = node->next);
    return (node != NULL);
}