/*
** EPITECH PROJECT, 2019
** my_rev_list
** File description:
** Reverse a linked list
*/

#include "mylist.h"

void my_rev_list(list_t *begin)
{
    int i = 0;
    long data_list[my_list_size(begin) + 1];
    list_t *node = begin;

    while (node != NULL) {
        data_list[i] = node->data;
        node = node->next;
        i += 1;
    }
    while (begin != NULL) {
        i -= 1;
        begin->data = data_list[i];
        begin = begin->next;
    }
}
