/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** read_file.c
*/

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "my.h"

static void *free_and_return(char *line, void *value)
{
    if (line != NULL)
        free(line);
    return (value);
}

static char **my_realloc_array(char **array, unsigned int to_add)
{
    int new_size = my_array_len(array) + to_add;
    char **new_array = malloc(sizeof(char *) * (new_size + 1));
    int i = 0;

    if (new_array != NULL) {
        for (i = 0; array != NULL && array[i] != NULL; i += 1)
            new_array[i] = array[i];
        while (i <= new_size) {
            new_array[i] = NULL;
            i += 1;
        }
        if (array != NULL)
            free(array);
    } else {
        my_free_array(array);
    }
    return (new_array);
}

char **read_file(char const *file)
{
    int i = 0;
    char **array = NULL;
    char *line = NULL;
    int fd = open(file, O_RDONLY);

    if (fd < 0)
        return NULL;
    while ((line = get_next_line(fd))) {
        array = my_realloc_array(array, 1);
        if (array == NULL)
            return (free_and_return(line, NULL));
        array[i] = line;
        i += 1;
    }
    close(fd);
    return (array);
}