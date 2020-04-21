/*
** EPITECH PROJECT, 2019
** my_str_to_word_array
** File description:
** Split a string in a word array
*/

#include <stdlib.h>
#include "my.h"

static int is_separator(char c, char const *separators)
{
    int i = 0;

    if (separators == NULL)
        return (0);
    while (separators[i] != '\0') {
        if (separators[i] == c)
            return (1);
        i += 1;
    }
    return (0);
}

static int get_nb_words(char const *str, char const *separators)
{
    int nb = 1;
    int i = 0;

    while (str[i] != '\0') {
        if (!is_separator(str[i], separators)) {
            i += 1;
            continue;
        }
        while (str[i] != '\0' && is_separator(str[i], separators))
            i += 1;
        if (str[i] != '\0')
            nb += 1;
    }
    return (nb);
}

static int get_index_end_word(char const *str, char const *separators)
{
    int i = 0;

    while (str[i] != '\0') {
        if (!is_separator(str[i], separators))
            i += 1;
        else
            break;
    }
    return (i);
}

static void generate_array(char **array, char const *str,
    int nb_words, char const *separators)
{
    int i = 0;
    int index_word;

    while (i < nb_words) {
        index_word = get_index_end_word(str, separators);
        array[i] = my_strndup(str, index_word);
        while (str[index_word] != '\0'
        && is_separator(str[index_word], separators))
            index_word += 1;
        str = &str[index_word];
        i += 1;
    }
}

char **my_str_to_word_array(char const *str, char const *separators)
{
    int nb_words;
    char **array;

    if (str == NULL)
        return (NULL);
    while (is_separator(str[0], separators))
        str = &str[1];
    if (my_strlen(str) == 0)
        return (NULL);
    nb_words = get_nb_words(str, separators);
    array = malloc(sizeof(char *) * (nb_words + 1));
    if (array == NULL)
        return (NULL);
    generate_array(array, str, nb_words, separators);
    array[nb_words] = NULL;
    return (array);
}
