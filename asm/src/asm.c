/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** asm.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "my.h"
#include "asm.h"

static char *my_strcat_malloc(char const *s1, char const *s2)
{
    char *final = malloc(sizeof(char) * (my_strlen(s1) + my_strlen(s2) + 1));
    int i = 0;

    if (final != NULL) {
        for (; s1[i]; i++) {
            final[i] = s1[i];
        }
        for (int f = 0; s2[f]; f++, i++) {
            final[i] = s2[f];
        }
        final[i] = '\0';
    }
    return final;
}

static char *get_output_file(char const *file)
{
    char extension[] = ".cor";
    char *file_without_extension = NULL;
    char *new_file = NULL;
    int dot = my_strchr_index(file, '.');

    if (dot < 0)
        return (my_strcat_malloc(file, extension));
    for (dot = my_strlen(file) - 1; file[dot] != '.'; dot -= 1);
    file_without_extension = my_strndup(file, dot);
    if (file_without_extension != NULL) {
        new_file = my_strcat_malloc(file_without_extension, extension);
        free(file_without_extension);
    }
    return (new_file);
}

static bool write_all(char const *file, header_t *header, char const *buffer)
{
    char *output_file = get_output_file(file);
    FILE *output = NULL;

    if (output_file == NULL)
        return (false);
    output = fopen(output_file, "w");
    if (output != NULL) {
        print_number(header->magic, output);
        fwrite(header->prog_name, sizeof(char), PROG_NAME_LENGTH, output);
        print_number(header->prog_size, output);
        fwrite(header->comment, sizeof(char), COMMENT_LENGTH, output);
        fwrite(buffer, sizeof(char), header->prog_size, output);
        fclose(output);
    }
    free(output_file);
    return (output != NULL);
}

int assembly(char const *file)
{
    header_t header;
    char *buffer = my_strdup("");
    char **array = read_file(file);

    if (array == NULL || buffer == NULL)
        return (84);
    remove_comments(array);
    if (!setup_header(array, &header))
        return (84);
    write_all(file, &header, buffer);
    my_free_array(array);
    free(buffer);
    return (0);
}