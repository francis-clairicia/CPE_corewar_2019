/*
** EPITECH PROJECT, 2019
** My_Lib_C
** File description:
** my_malloc_array.c
*/

#include <sys/types.h>
#include <stdlib.h>

void *my_memset(void *buffer, int c, size_t size);

void my_free_array(void *array)
{
    void **ptr = array;
    int i = 0;

    if (array == NULL)
        return;
    for (i = 0; ptr[i] != NULL; i += 1)
        free(ptr[i]);
    free(ptr);
}

void *my_malloc_array(size_t width, size_t height, size_t size)
{
    void **array = malloc(sizeof(void *) * (height + 1));
    size_t i = 0;

    if (array == NULL)
        return (NULL);
    for (i = 0; i < height; i += 1) {
        array[i] = malloc(size * width);
        if (array[i] == NULL) {
            return (NULL);
        }
        my_memset(array[i], 0, size * width);
    }
    array[height] = NULL;
    return (array);
}