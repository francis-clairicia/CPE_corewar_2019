/*
** EPITECH PROJECT, 2019
** My_Lib_C
** File description:
** my_concat_str_list.c
*/

#include "mylist.h"

int my_strlen(char const *str);

static int get_str_size(list_t list, char separator)
{
    node_t *begin = list.start;
    int str_size = 0;
    int has_separator = (separator != '\0');
    int nb_separators = (has_separator) * (list.size - 1);

    while (begin != NULL) {
        str_size += my_strlen(NODE_DATA(begin, char *));
        begin = begin->next;
    }
    return (str_size + nb_separators);
}

static int fill_str(char *str, int i, char *element)
{
    int j = 0;

    while (element[j] != '\0') {
        str[i] = element[j];
        i += 1;
        j += 1;
    }
    return (i);
}

char *my_concat_str_list(list_t list, char separator, int *len)
{
    node_t *begin = list.start;
    int str_size = get_str_size(list, separator);
    char *str = malloc(sizeof(char) * (str_size + 1));
    int i = 0;

    while (begin != NULL) {
        i = fill_str(str, i, NODE_DATA(begin, char *));
        begin = begin->next;
        if (begin != NULL && separator != '\0') {
            str[i] = separator;
            i += 1;
        }
    }
    str[str_size] = 0;
    *len = str_size;
    return (str);
}