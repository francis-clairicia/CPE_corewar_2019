/*
** EPITECH PROJECT, 2019
** My_Lib_C
** File description:
** my_concat_str_list.c
*/

#include "mylist.h"

int my_strlen(char const *str);

static int get_str_size(list_t *begin, char separator)
{
    int str_size = 0;
    int has_separator = (separator != '\0');
    int nb_separators = (has_separator) * (my_list_size(begin) - 1);

    while (begin != NULL) {
        str_size += my_strlen((char *)(begin->data));
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

char *my_concat_str_list(list_t *begin, char separator, int *len)
{
    int str_size = get_str_size(begin, separator);
    char *str = malloc(sizeof(char) * (str_size + 1));
    int i = 0;

    while (begin != NULL) {
        i = fill_str(str, i, (char *)(begin->data));
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