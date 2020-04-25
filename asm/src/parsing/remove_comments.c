/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** remove_comments.c
*/

#include <stdlib.h>
#include "asm.h"
#include "my.h"
#include "op.h"

static void move_all_up(char **array, int index)
{
    free(array[index]);
    while (array[index] != NULL) {
        array[index] = array[index + 1];
        index += 1;
    }
}

void remove_comments(char **array)
{
    int sharp = 0;

    if (array == NULL)
        return;
    for (register int i = 0; array[i]; i += 1) {
        if (array[i][0] == COMMENT_CHAR || array[i][0] == '\0') {
            move_all_up(array, i);
            i -= 1;
            continue;
        }
        sharp = my_strchr_index(array[i], COMMENT_CHAR);
        if (sharp > 0)
            array[i][sharp] = '\0';
    }
}