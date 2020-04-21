/*
** EPITECH PROJECT, 2019
** my_list_size
** File description:
** Returns the size of a linked list
*/

#include "mylist.h"

int my_list_size(list_t *begin)
{
    int size = 0;

    while (begin != NULL) {
        size += 1;
        begin = begin->next;
    }
    return (size);
}
