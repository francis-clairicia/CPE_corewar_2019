/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** header
*/

#include "my.h"
#include "op.h"

static bool copy_str_value(char *line, char *cmd, int max_length)
{
    char *name = my_strchr(line, '"');
    int end = 0;

    if (name == NULL)
        return (false);
    name = &name[1];
    my_memset(cmd, '\0', max_length + 1);
    end = my_strchr_index(name, '"');
    if (end < 0)
        return (false);
    if (end > max_length)
        return (false);
    my_strncpy(cmd, name, end);
    return (true);
}

bool setup_header(char **array, header_t *header)
{
    int len_name = my_strlen(NAME_CMD_STRING);
    int len_comment = my_strlen(COMMENT_CMD_STRING);

    if (array == NULL || header == NULL)
        return (false);
    if (my_strncmp(array[0], NAME_CMD_STRING, len_name) != 0)
        return (false);
    if (my_strncmp(array[1], COMMENT_CMD_STRING, len_comment) != 0)
        return (false);
    if (!copy_str_value(array[0], header->prog_name, PROG_NAME_LENGTH))
        return (false);
    if (!copy_str_value(array[1], header->comment, COMMENT_LENGTH))
        return (false);
    header->magic = COREWAR_EXEC_MAGIC;
    header->prog_size = 0;
    return (true);
}
