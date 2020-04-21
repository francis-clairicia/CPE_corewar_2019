/*
** EPITECH PROJECT, 2019
** My swap
** File description:
** Swap two numbers using their addresses
*/

#include <stddef.h>

void my_swap(int *a, int *b)
{
    int c = 0;

    if (a != NULL && b != NULL) {
        c = *a;
        *a = *b;
        *b = c;
    }
}
