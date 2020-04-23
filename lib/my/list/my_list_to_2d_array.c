/*
** EPITECH PROJECT, 2019
** My_Lib_C
** File description:
** my_list_to_2d_array.c
*/

#include "mylist.h"

void *my_list_to_2d_array(list_t *list, int free_list)
{
    int i = 0;
    node_t *node = NULL;
    void **array = (!list) ? NULL : malloc(sizeof(void *) * (list->size + 1));

    if (array != NULL) {
        for (node = list->start; node != NULL; node = node->next) {
            array[i] = NODE_DATA(node, void *);
            i += 1;
        }
        array[i] = NULL;
    }
    if (free_list)
        my_free_list(list, NULL);
    return (array);
}