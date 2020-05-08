/*
** EPITECH PROJECT, 2019
** asm
** File description:
** parse_line.c
*/

#include <stdlib.h>
#include "asm.h"
#include "my.h"
#include "mylist.h"

static errno_t free_and_return(char *str1, char *str2, char **array,
    errno_t errno)
{
    if (str1 != NULL)
        free(str1);
    if (str2 != NULL)
        free(str2);
    if (array != NULL)
        my_free_array(array);
    return (errno);
}

static char const *skip_first_spaces(char const *str)
{
    if (str != NULL) {
        while (str[0] != '\0' && str[0] == ' ')
            str = &str[1];
    }
    return (str);
}

static char const *check_for_label(char const *line, int *space, char **label)
{
    int last = my_strlen(line) - 1;

    *space = my_strchr_index(line, ' ');
    if (*space < 0) {
        if (line[last] == LABEL_CHAR) {
            *label = my_strndup(line, last);
            line = skip_first_spaces(&(line[last + 1]));
        }
        return (line);
    }
    last = *space - 1;
    if (line[last] != LABEL_CHAR)
        return (line);
    *label = my_strndup(line, last);
    line = skip_first_spaces(&(line[last + 1]));
    *space = my_strchr_index(line, ' ');
    return (line);
}

static errno_t parse_instruction(list_t *list, char *mnemonic, char **params,
    char *label)
{
    int index = -1;
    instruction_t instruction;
    errno_t error = E_SUCCESS;

    if (!valid_label(label, &error))
        return (free_and_return(mnemonic, label, params, error));
    if (mnemonic != NULL && !valid_instruction(mnemonic, &index, &error))
        return (free_and_return(mnemonic, label, params, error));
    if (mnemonic != NULL && !valid_parameters(params, index, &error))
        return (free_and_return(mnemonic, label, params, error));
    instruction = init_instruction(index, params, label);
    my_append_to_list(list, instruction, instruction_t);
    return (free_and_return(mnemonic, NULL, NULL, E_SUCCESS));
}

errno_t parse_line(char const *line, list_t *list)
{
    char *mnemonic = NULL;
    char **params = NULL;
    char separator[] = {SEPARATOR_CHAR, '\0'};
    char *label = NULL;
    int space = 0;

    if (!line || !list)
        return (E_INTERNAL_ERROR);
    line = skip_first_spaces(line);
    line = check_for_label(line, &space, &label);
    if (my_strlen(line) > 0) {
        if (space < 0)
            space = my_strlen(line);
        mnemonic = my_strndup(line, space);
        params = my_str_to_word_array(&line[space], separator);
    }
    return (parse_instruction(list, mnemonic, params, label));
}