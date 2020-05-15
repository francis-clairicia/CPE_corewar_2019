/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** header
*/

#include "asm.h"
#include "my.h"

static bool print_and_return(char const *file, int line, errno_t errno)
{
    print_error(file, line, errno);
    return (false);
}

static bool copy_str_value(line_t const *line, char *cmd, int max_length,
    errno_t cmd_err)
{
    char *name = my_strchr((char *)(line->content), '"');
    int end = 0;

    if (name == NULL)
        return (print_and_return(line->file, line->nb, E_INTERNAL_ERROR));
    name = &name[1];
    my_memset(cmd, '\0', max_length + 1);
    end = my_strchr_index(name, '"');
    if (end < 0 || name[end + 1] != '\0')
        return (print_and_return(line->file, line->nb, E_INVALID_SYNTAX));
    if (end > max_length)
        return (print_and_return(line->file, line->nb, cmd_err));
    my_strncpy(cmd, name, end);
    return (true);
}

static bool valid_command(line_t const *line, char const *cmd, errno_t cmd_err)
{
    char const *instruction = skip_first_spaces(line->content);
    int len = my_strlen(cmd);

    if (my_strncmp(instruction, cmd, len) != 0)
        return (print_and_return(line->file, line->nb, cmd_err));
    if (!my_strchr(" \t", instruction[len]))
        return (print_and_return(line->file, line->nb, E_INVALID_INSTRUCTION));
    for (; my_strchr(" \t", instruction[len]); len += 1);
    if (instruction[len] != '"')
        return (print_and_return(line->file, line->nb, E_INVALID_SYNTAX));
    return (true);
}

bool setup_header(line_t * const *array, header_t *header)
{
    if (!array || my_array_len(array) < 2 || !header)
        return (false);
    if (!valid_command(array[0], NAME_CMD_STRING, E_NO_NAME))
        return (false);
    if (!valid_command(array[1], COMMENT_CMD_STRING, E_NO_COMMENT))
        return (false);
    if (!copy_str_value(array[0], header->prog_name, PROG_NAME_LENGTH,
        E_TOO_LONG_NAME))
        return (false);
    if (!copy_str_value(array[1], header->comment, COMMENT_LENGTH,
        E_TOO_LONG_COMMENT))
        return (false);
    header->magic = COREWAR_EXEC_MAGIC;
    header->prog_size = 0;
    return (true);
}
