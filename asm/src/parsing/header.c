/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** header
*/

#include "my.h"
#include "op.h"
#include "asm.h"

static bool free_and_return(char **array, bool value)
{
    if (array != NULL)
        my_free_array(array);
    return (value);
}

static bool copy_str_value(char const *line, char *cmd, int max_length)
{
    int len_line = my_strlen(line);
    char copy_line[len_line];
    int end = len_line - 1;

    if (line[0] != '"' || line[end] != '"')
        return (false);
    my_strncpy(copy_line, &line[1], end - 1);
    my_memset(cmd, '\0', max_length + 1);
    if (my_strchr_index(copy_line, '"') >= 0
    || my_strlen(copy_line) > max_length)
        return (false);
    my_strcpy(cmd, copy_line);
    return (true);
}

static bool set_header_field(char **array, char const *instruction,
    char *cmd, int max_length)
{
    bool already_set = false;
    int len_instruction = my_strlen(instruction);
    char **line = NULL;

    for (int i = 0; array[i]; i += 1) {
        if (my_strncmp(array[i], instruction, len_instruction) != 0)
            continue;
        line = parse_line(array[i], " \t", false);
        if (line == NULL)
            return (false);
        if (my_strcmp(line[0], instruction) != 0 || my_array_len(line) != 2)
            return (free_and_return(line, false));
        if (already_set || !copy_str_value(line[1], cmd, max_length))
            return (free_and_return(line, false));
        already_set = true;
        my_free_array(line);
    }
    return (true);
}

bool setup_header(char **array, header_t *header)
{
    char *name = NULL;
    char *comment = NULL;

    if (array == NULL || my_array_len(array) < 2 || header == NULL)
        return (false);
    name = header->prog_name;
    comment = header->comment;
    if (!set_header_field(array, NAME_CMD_STRING, name, PROG_NAME_LENGTH))
        return (false);
    if (!set_header_field(array, COMMENT_CMD_STRING, comment, COMMENT_LENGTH))
        return (false);
    header->magic = COREWAR_EXEC_MAGIC;
    header->prog_size = 0;
    return (true);
}
