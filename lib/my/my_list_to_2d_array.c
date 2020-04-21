/*
** EPITECH PROJECT, 2019
** My_Lib_C
** File description:
** my_list_to_2d_array.c
*/

#include "mylist.h"

void *my_list_to_2d_array(list_t **list, int free_list)
{
    int i = 0;
    int size = my_list_size(*list);
    list_t *node = NULL;
    void **array = malloc(sizeof(void *) * (size + 1));

    if (array != NULL) {
        for (node = *list; node != NULL; node = node->next) {
            array[i] = NODE_DATA(node, void *);
            i += 1;
        }
        array[i] = NULL;
    }
    if (free_list)
        my_free_list(list, NULL);
    return (array);
}