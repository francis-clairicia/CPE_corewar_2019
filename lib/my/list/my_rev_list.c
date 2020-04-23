/*
** EPITECH PROJECT, 2019
** my_rev_list
** File description:
** Reverse a linked list
*/

#include "mylist.h"

void my_rev_list(list_t list)
{
    int i = 0;
    data_node_t data_list[list.size + 1];
    node_t *node = NULL;

    for (node = list.start; node != NULL; node = node->next) {
        data_list[i] = node->data;
        i += 1;
    }
    for (node = list.start; node != NULL; node = node->next) {
        i -= 1;
        node->data = data_list[i];
    }
}
