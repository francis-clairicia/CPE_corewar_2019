/*
** EPITECH PROJECT, 2019
** My_Lib_C
** File description:
** join_path.c
*/

#include <stdlib.h>

int my_strlen(char const *str);

static int get_path_size(char const *path_1, char const *path_2, int *slash)
{
    int len = my_strlen(path_1);

    if (path_1[len - 1] != '/')
        *slash = 1;
    return (len + *slash + my_strlen(path_2));
}

static int copy_str(char *dest, char const *src, int start)
{
    int i = 0;

    while (src[i] != '\0') {
        dest[start + i] = src[i];
        i += 1;
    }
    return (start + i);
}

char *join_path(char const *path_1, char const *path_2)
{
    int start = 0;
    int slash = 0;
    int new_path_size = get_path_size(path_1, path_2, &slash);
    char *new_path = malloc(sizeof(char) * (new_path_size + 1));

    if (new_path == NULL)
        return (NULL);
    start = copy_str(new_path, path_1, start);
    if (slash)
        start = copy_str(new_path, "/", start);
    copy_str(new_path, path_2, start);
    new_path[new_path_size] = '\0';
    return (new_path);
}