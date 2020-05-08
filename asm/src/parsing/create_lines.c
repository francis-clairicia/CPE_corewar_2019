/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** remove_comments.c
*/

#include <stdlib.h>
#include "asm.h"
#include "my.h"
#include "mylist.h"

static void move_all_up(char **array, int index)
{
    free(array[index]);
    while (array[index] != NULL) {
        array[index] = array[index + 1];
        index += 1;
    }
}

static bool remove_comments(char **content, int i)
{
    int comment = 0;

    if (content[i][0] == '\0' || content[i][0] == COMMENT_CHAR
    || my_str_contains_only(content[i], " ")) {
        move_all_up(content, i);
        return (true);
    }
    comment = my_strchr_index(content[i], COMMENT_CHAR);
    if (comment > 0)
        content[i][comment] = '\0';
    return (false);
}

static bool add_new_line(list_t *list, int line_nb, char *line_str)
{
    line_t *line = malloc(sizeof(*line));

    if (!line)
        return (false);
    line->nb = line_nb;
    line->content = line_str;
    if (!my_append_to_list(list, line, line_t *)) {
        free(line);
        my_free_list(list, &free);
        return (false);
    }
    return (true);
}

line_t **create_lines(char **content)
{
    register int i = 0;
    int line_nb = 0;
    list_t list = my_list();

    if (content == NULL)
        return (NULL);
    while (content[i] != NULL) {
        line_nb += 1;
        if (remove_comments(content, i))
            continue;
        if (!add_new_line(&list, line_nb, content[i]))
            return (NULL);
        i += 1;
    }
    return (my_list_to_2d_array(&list, true));
}