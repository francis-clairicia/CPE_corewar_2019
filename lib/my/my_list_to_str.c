/*
** EPITECH PROJECT, 2019
** my_list_to_string
** File description:
** Put data (char) in string
*/

#include "mylist.h"

char *my_list_to_str(list_t *list)
{
    int size_list = my_list_size(list);
    char *str = malloc(sizeof(char) * (size_list + 1));
    int i = 0;
    list_t *node = list;

    if (str != NULL) {
        while (node != NULL) {
            str[i] = (char)(node->data);
            i += 1;
            node = node->next;
        }
        str[i] = '\0';
    }
    return (str);
}
