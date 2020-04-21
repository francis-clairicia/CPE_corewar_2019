/*
** EPITECH PROJECT, 2019
** mylist.h
** File description:
** Header for linked list functions
*/

#ifndef HEADER_MY_LIST
#define HEADER_MY_LIST

#include <stdlib.h>

typedef struct linked_list
{
    long data;
    struct linked_list *previous;
    struct linked_list *next;
} list_t;

list_t *my_list(int nb_element, ...);
int my_list_size(list_t *begin);
int my_put_in_list(list_t **list, long data);
int my_append_to_list(list_t **list, long data);
void my_concat_list(list_t **begin1, list_t *begin2);
void my_free_list(list_t **list, void (*free_function)());
void my_rev_list(list_t *begin);
char *my_list_to_str(list_t *list);
char *my_concat_str_list(list_t *begin, char separator, int *len);
list_t *my_node(list_t *begin, int index);
list_t *my_node_from_data(list_t *begin, long data, int *index);
list_t *my_find_node(list_t *list, list_t *node_to_find, int *index);
void my_delete_node(list_t **list, int i, void (*free_function)());
void my_delete_node_from_data(list_t **list, long data, void (*free_func)());
void my_delete_node_from_node(list_t **list, list_t *node, void (*free_func)());
void *my_list_to_2d_array(list_t **list, int free_list);

#define MY_APPEND_TO_LIST(list, data) my_append_to_list(list, (long)data)
#define MY_PUT_IN_LIST(list, data) my_put_in_list(list, (long)data)
#define NODE_DATA(node, cast) ((node != NULL) ? ((cast)(node->data)) : (cast)0)

#endif
