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

static bool free_and_return(char *str1, char *str2, char **array)
{
    if (str1 != NULL)
        free(str1);
    if (str2 != NULL)
        free(str2);
    if (array != NULL)
        my_free_array(array);
    return (my_errno == E_SUCCESS);
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

static bool parse_instruction(list_t *list, char *mnemonique, char **params,
    char *label)
{
    int index = -1;
    instruction_t instruction;

    if (!valid_label(label))
        return (free_and_return(mnemonique, label, params));
    if (mnemonique != NULL && !valid_instruction(mnemonique, &index))
        return (free_and_return(mnemonique, label, params));
    if (mnemonique != NULL && !valid_parameters(params, index))
        return (free_and_return(mnemonique, label, params));
    instruction = init_instruction(index, params, label);
    my_append_to_list(list, instruction, instruction_t);
    return (free_and_return(mnemonique, NULL, NULL));
}

bool parse_line(char const *line, list_t *list)
{
    char *mnemonique = NULL;
    char **params = NULL;
    char separator[] = {SEPARATOR_CHAR, '\0'};
    char *label = NULL;
    int space = 0;

    if (!line || !list)
        return (set_errno(E_INTERNAL_ERROR));
    line = skip_first_spaces(line);
    line = check_for_label(line, &space, &label);
    if (my_strlen(line) > 0) {
        if (space < 0)
            space = my_strlen(line);
        mnemonique = my_strndup(line, space);
        params = my_str_to_word_array(&line[space], separator);
    }
    return (parse_instruction(list, mnemonique, params, label));
}