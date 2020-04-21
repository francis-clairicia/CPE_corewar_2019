/*
** EPITECH PROJECT, 2019
** my_concat_list
** File description:
** Concatenate two linked lists
*/

#include "mylist.h"

void my_concat_list(list_t **begin1, list_t *begin2)
{
    list_t *last_node;

    if ((*begin1) == NULL) {
        (*begin1) = begin2;
    } else if (begin2 != NULL){
        last_node = (*begin1)->previous;
        last_node->next = begin2;
        (*begin1)->previous = begin2->previous;
        begin2->previous = last_node;
    }
}
