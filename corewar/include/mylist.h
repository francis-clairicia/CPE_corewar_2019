/*
** EPITECH PROJECT, 2019
** mylist.h
** File description:
** Header for linked list functions
*/

#ifndef HEADER_MY_LIST
#define HEADER_MY_LIST

#include <stdlib.h>

typedef struct data_node
{
    void *ptr;
    size_t size;
} data_node_t;

typedef struct node_list
{
    data_node_t data;
    size_t index;
    struct node_list *previous;
    struct node_list *next;
} node_t;

typedef struct linked_list
{
    node_t *start;
    node_t *end;
    size_t size;
} list_t;


/////////// Init a linked list ///////////
// This function will set default values to the list_t struct
list_t my_list(void);
//////////////////////////////////////////

/////////// Destroy a linked list or a node of this ///////////
// (free_function is a pointer to the function to use to free if this list
// was a list of pointers)
//
// Free the whole linked list
void my_free_list(list_t *list, void (*free_function)());
//
// Delete the node at a certain index
// (If 'index' is negative the search will begin at the end)
void my_delete_node(list_t *list, int index, void (*free_function)());
//
// Delete the first occurence of a node according to a data
#define my_delete_node_data(list, data, type, func) \
    _DEL_DATA(list, data, type, func)
//
// Remove a node pointer from a list and free it
void my_delete_node_from_node(list_t *list, node_t *node, void (*free_func)());
///////////////////////////////////////////////////////////////


///////////// Add data to linked lists ///////////
//// All of theses function return 1 if it was a success, 0 otherwise
// Insert a node into a linked list
// (If 'copy' is not 0, the function create a new node with the data of the node
// passed in parameter)
int my_insert_node(list_t *list, node_t *node, int index, int copy);
//
// Insert a data at a certain index
// (If 'index' is negative the search will begin at the end)
#define my_insert_data(list, data, type, index) \
    _INSERT_DATA(list, data, type, index)
//
// Insert a data at the begin of the list
#define my_put_in_list(list, data, type) \
    _INSERT_DATA(list, data, type, 0)
//
// Insert a data at the end of the list
#define my_append_to_list(list, data, type) \
    _INSERT_DATA(list, data, type, -1)
//////////////////////////////////////////////////

///////////// Get/Find node in list /////////////
// Get the node pointer at index, return NULL if none was found
// (If 'index' is negative the search will begin at the end)
node_t *my_node(list_t list, int index);
//
// Check if a node is in a list
// Return 1 if it's true, 0 otherwise
int my_find_node(list_t list, const node_t *to_find);
//
// Get the first occurence of a node according to a data, NULL otherewise
#define my_node_from_data(list, data, type) _GET_NODE(list, data, type)
/////////////////////////////////////////////////


///////////// Useful functions /////////////
void my_concat_list(list_t *list1, list_t *list2);
void my_rev_list(list_t list);
char *my_list_to_str(list_t list);
char *my_concat_str_list(list_t list, char separator, int *len);
void *my_list_to_2d_array(list_t *list, int free_list);
////////////////////////////////////////////


///////////// Macros to get a data from a node_t struct pointer /////////////
// Get a pointer to the data inside the node
#define NODE_DATA_PTR(node, type) ((type *)((node)->data.ptr))
//
// Get the value of the data inside the node
#define NODE_DATA(node, type) (*NODE_DATA_PTR(node, type))
/////////////////////////////////////////////////////////////////////////////


/////////// Internal functions/Macros used for linked lists ///////////
// You don't have to use it !
// Use the macros above instead.
node_t *_create_node(const void *data, size_t size);
node_t *_node_from_data(list_t list, const void *data, size_t size);
void _delete_node_from_data(list_t *list, const void *data, size_t size,
    void (*free_func)());
#define _FDATA(data, type) (type [1]){data}, sizeof(type)
#define _INSERT_DATA(list, data, type, index) \
    my_insert_node(list, _create_node(_FDATA(data, type)), index, 0)
#define _GET_NODE(list, data, type) _node_from_data(list, _FDATA(data, type))
#define _DEL_DATA(list, data, type, func) \
    _delete_node_from_data(list, _FDATA(data, type), func)
//////////////////////////////////////////////////////////////////////

#endif
