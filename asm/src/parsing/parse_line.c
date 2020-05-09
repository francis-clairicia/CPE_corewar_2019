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

static char const *check_for_label(char const *line, char **label)
{
    int last = 0;
    char **parsed = my_str_to_word_array(line, " \t");

    if (!parsed || !(parsed[0]))
        return (line);
    last = my_strlen(parsed[0]) - 1;
    if (parsed[0][last] == LABEL_CHAR) {
        *label = my_strndup(parsed[0], last);
        line = my_strstr((char *)(&line[last + 1]), parsed[1]);
    }
    my_free_array(parsed);
    return (line);
}

static void get_mnemonic_and_params(char const *line,
    char **mnemonic, char ***params)
{
    char **parsed = my_str_to_word_array(line, " \t");
    char separator[] = {SEPARATOR_CHAR, '\0'};

    if (!parsed)
        return;
    *mnemonic = parsed[0];
    *params = my_str_to_word_array(&line[my_strlen(parsed[0])], separator);
    for (int i = 1; parsed[i] != NULL; i += 1)
        free(parsed[i]);
    free(parsed);
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
    char *label = NULL;

    if (!line || !list)
        return (E_INTERNAL_ERROR);
    line = skip_first_spaces(line);
    line = check_for_label(line, &label);
    if (my_strlen(line) > 0)
        get_mnemonic_and_params(line, &mnemonic, &params);
    return (parse_instruction(list, mnemonic, params, label));
}