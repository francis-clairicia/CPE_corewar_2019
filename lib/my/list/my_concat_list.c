/*
** EPITECH PROJECT, 2019
** my_concat_list
** File description:
** Concatenate two linked lists
*/

#include "mylist.h"

void my_concat_list(list_t *list1, list_t *list2)
{
    int i = 0;
    node_t *node = NULL;

    if (list1 == NULL || list2 == NULL)
        return;
    if (list1->size == 0) {
        *list1 = *list2;
    } else if (list2->size > 0) {
        list1->end->next = list2->start;
        list2->start->previous = list1->end;
        list1->end = list2->end;
        i = list1->size;
        for (node = list2->start; node != NULL; node = node->next)
            node->index = i++;
        list1->size += list2->size;
    }
    *list2 = my_list();
}
