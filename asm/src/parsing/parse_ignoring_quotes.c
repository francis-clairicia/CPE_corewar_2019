/*
** EPITECH PROJECT, 2019
** asm
** File description:
** parse_ignoring_quotes.c
*/

#include "my.h"
#include "mylist.h"

static int skip_quotes(char const *str, char quote, int index)
{
    do
        index += 1;
    while (str[index] != '\0' && str[index] != quote);
    return (index);
}

static void skip_separators(char const *input, char const separators[],
    int *index, int *start)
{
    while (input[*index] != '\0'
    && my_strchr_index(separators, input[*index]) >= 0)
        *index += 1;
    *start = *index;
    if (input[*index] == '\0')
        *index -= 1;
}

static void add_arg(list_t *list, char const *input, int bounds[2], bool rm)
{
    int size = bounds[1] - bounds[0];
    char *arg = (size == 0) ? NULL : malloc(sizeof(char) * (size + 1));
    char quotes[3] = {'\'', '"', '\0'};
    int quote = 0;
    int save = 0;

    if (my_memset(arg, 0, size + 1) == NULL)
        return;
    while (bounds[0] < bounds[1]) {
        quote = my_strchr_index(quotes, input[bounds[0]]);
        if (rm == true && quote >= 0) {
            save = bounds[0];
            bounds[0] = skip_quotes(input, quotes[quote], bounds[0]);
            my_strncat(arg, &input[save + 1], bounds[0] - save - 1);
        } else
            my_strncat(arg, &input[bounds[0]], 1);
        bounds[0] += 1;
    }
    my_append_to_list(list, arg, char *);
}

static bool stop_arg(char input, char *quote, char const separators[])
{
    char quotes[3] = {'\'', '"', '\0'};
    int quote_index = my_strchr_index(quotes, input);

    if (*quote != 0) {
        if (input == *quote)
            *quote = 0;
        return (false);
    }
    if (quote_index != -1) {
        *quote = quotes[quote_index];
        return (false);
    }
    return (my_strchr_index(separators, input) >= 0);
}

char **parse_line(char const *input, char const separators[], bool remove)
{
    list_t list = my_list();
    int i = 0;
    char quote = 0;
    int start = 0;

    if (input == NULL)
        return (NULL);
    for (i = 0; input[i] != '\0'; i += 1) {
        if (i == start)
            skip_separators(input, separators, &i, &start);
        if (input[start] != '\0' && stop_arg(input[i], &quote, separators)) {
            add_arg(&list, input, (int []){start, i}, remove);
            start = i + 1;
        }
    }
    if (start != i)
        add_arg(&list, input, (int []){start, i}, remove);
    return (my_list_to_2d_array(&list, true));
}