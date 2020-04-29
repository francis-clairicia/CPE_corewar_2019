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

void remove_comments(char **content)
{
    int sharp = 0;

    if (content == NULL)
        return;
    for (register int i = 0; content[i]; i += 1) {
        if (content[i][0] == COMMENT_CHAR || content[i][0] == '\0') {
            move_all_up(content, i);
            i -= 1;
            continue;
        }
        sharp = my_strchr_index(content[i], COMMENT_CHAR);
        if (sharp > 0)
            content[i][sharp] = '\0';
    }
}