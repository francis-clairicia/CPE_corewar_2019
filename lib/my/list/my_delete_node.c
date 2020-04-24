/*
** EPITECH PROJECT, 2019
** My_Lib_C
** File description:
** my_delete_node.c
*/

#include "mylist.h"

static void delete_first_node(list_t *list)
{
    int i = 0;
    node_t *node = NULL;

    if (list->size == 1) {
        list->start = NULL;
        list->end = NULL;
    } else {
        list->start = list->start->next;
        list->start->previous = NULL;
        for (node = list->start; node != NULL; node = node->next)
            node->index = i++;
    }
}

static void delete_middle_node(node_t *node)
{
    node_t *previous_node;
    node_t *next_node;
    int index = node->index;

    previous_node = node->previous;
    next_node = node->next;
    previous_node->next = next_node;
    next_node->previous = previous_node;
    for (node = next_node; node != NULL; node = node->next)
        node->index = index++;
}

static void delete_last_node(list_t *list)
{
    list->end = list->end->previous;
    list->end->next = NULL;
}

static void free_node(node_t *node, void (*free_function)())
{
    if (free_function != NULL && NODE_DATA(node, void *) != NULL)
        free_function(NODE_DATA(node, void *));
    free(node->data.ptr);
    free(node);
}

void my_delete_node(list_t *list, int index, void (*free_function)())
{
    node_t *node = NULL;

    if (list == NULL)
        return;
    node = my_node(*list, index);
    if (node == NULL)
        return;
    if (node == list->start)
        delete_first_node(list);
    else if (node == list->end)
        delete_last_node(list);
    else
        delete_middle_node(node);
    free_node(node, free_function);
    list->size -= 1;
}