/*
** EPITECH PROJECT, 2019
** My_Lib_C
** File description:
** my_array_dup.c
*/

#include <stdlib.h>

int my_array_len(char * const *array);

void my_free_array(void *array);

char *my_strdup(char const *str);

char **my_array_dup(char * const * src)
{
    int i = 0;
    char **dest = NULL;

    if (src == NULL)
        return (NULL);
    dest = malloc(sizeof(char *) * (my_array_len(src) + 1));
    if (dest == NULL)
        return (NULL);
    while (src[i] != NULL) {
        dest[i] = my_strdup(src[i]);
        if (dest[i] == NULL) {
            my_free_array(dest);
            return (NULL);
        }
        i += 1;
    }
    dest[i] = NULL;
    return (dest);
}