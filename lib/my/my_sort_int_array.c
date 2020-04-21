/*
** EPITECH PROJECT, 2019
** My sort int array
** File description:
** Sort integers inside an array
*/

#include <stddef.h>

static int test_array_int(int *array, int size)
{
    int i = 1;
    int test_result = 0;

    while (i < size) {
        if (array[i - 1] > array[i])
            test_result = 1;
        i += 1;
    }
    return (test_result);
}

static void sort_array_int(int *array, int size)
{
    int i = 1;
    int stock = 0;

    while (i < size) {
        if (array[i - 1] > array[i]) {
            stock = array[i - 1];
            array[i - 1] = array[i];
            array[i] = stock;
        }
        i += 1;
    }
}

void my_sort_int_array(int *array, int size)
{
    if (array != NULL) {
        while (test_array_int(array, size) == 1)
            sort_array_int(array, size);
    }
}
