/*
** EPITECH PROJECT, 2019
** My_Lib_C
** File description:
** my_memset.c
*/

#include <sys/types.h>
#include <stddef.h>

void *my_memset(void *buffer, int c, size_t size)
{
    unsigned int i = 0;

    if (buffer == NULL)
        return (NULL);
    while (i < size) {
        ((char *)buffer)[i] = c;
        i += 1;
    }
    return (buffer);
}