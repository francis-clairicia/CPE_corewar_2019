/*
** EPITECH PROJECT, 2019
** my_list_to_string
** File description:
** Put data (char) in string
*/

#include "mylist.h"

char *my_list_to_str(list_t list)
{
    char *str = malloc(sizeof(char) * (list.size + 1));
    int i = 0;
    node_t *node = list.start;

    if (str != NULL) {
        while (node != NULL) {
            str[i] = NODE_DATA(node, char);
            i += 1;
            node = node->next;
        }
        str[i] = '\0';
    }
    return (str);
}
