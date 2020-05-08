/*
** EPITECH PROJECT, 2019
** My_Lib_C
** File description:
** get_next_line_2.c
*/

#include <stdlib.h>

char *get_next_line(int fd);

int get_next_line_2(char **line, int fd)
{
    if (line == NULL)
        return (0);
    if (*line != NULL)
        free(*line);
    *line = get_next_line(fd);
    return (*line != NULL);
}