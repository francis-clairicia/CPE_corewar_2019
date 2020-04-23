/*
** EPITECH PROJECT, 2019
** My_Lib_C
** File description:
** my_list.c
*/

#include "mylist.h"

list_t my_list(void)
{
    list_t list;

    list.start = NULL;
    list.end = NULL;
    list.size = 0;
    return (list);
}