/*
** EPITECH PROJECT, 2019
** My_Lib_C
** File description:
** my_delete_node.c
*/

#include "mylist.h"

static void delete_first_node(list_t **list, void (*free_function)())
{
    if ((*list)->next == NULL) {
        my_free_list(list, free_function);
        return;
    }
    (*list)->next->previous = (*list)->previous;
    *list = (*list)->next;
}

static void delete_middle_node(list_t *node)
{
    list_t *previous_node;
    list_t *next_node;

    previous_node = node->previous;
    next_node = node->next;
    previous_node->next = next_node;
    next_node->previous = previous_node;
}

static void delete_last_node(list_t **list)
{
    list_t *last_node = (*list)->previous;
    list_t *previous_of_last_node = last_node->previous;

    (*list)->previous = previous_of_last_node;
    previous_of_last_node->next = NULL;
}

void my_delete_node(list_t **list, int i, void (*free_function)())
{
    list_t *node = my_node(*list, i);

    if (node == NULL)
        return;
    if (node == *list) {
        delete_first_node(list, free_function);
        if (*list == NULL)
            return;
    } else if (node == (*list)->previous){
        delete_last_node(list);
    } else {
        delete_middle_node(node);
    }
    node->next = NULL;
    my_free_list(&node, free_function);
}