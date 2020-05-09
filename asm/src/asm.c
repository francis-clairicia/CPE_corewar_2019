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
    int dot = my_strlen(file) - 1;

    for (; dot >= 0 && !my_strchr("/.", file[dot]); dot -= 1);
    if (dot < 0 || file[dot] == '/')
        return (my_strcat_malloc(file, extension));
    file_without_extension = my_strndup(file, dot);
    if (file_without_extension != NULL) {
        new_file = my_strcat_malloc(file_without_extension, extension);
        free(file_without_extension);
    }
    return (new_file);
}

static int write_all(char const *file, header_t *header, char const *buffer)
{
    char *output_file = get_output_file(file);
    FILE *output = NULL;

    if (output_file == NULL)
        return (84);
    output = fopen(output_file, "wb");
    if (output != NULL) {
        header->magic = REVERSED_NB(header->magic);
        header->prog_size = REVERSED_NB(header->prog_size);
        fwrite(header, sizeof(*header), 1, output);
        header->prog_size = REVERSED_NB(header->prog_size);
        if (buffer != NULL)
            fwrite(buffer, sizeof(char), header->prog_size, output);
        fclose(output);
    }
    free(output_file);
    return (84 * (output == NULL));
}

int assembly(char const *file)
{
    header_t header;
    char *buffer = NULL;
    char **content = read_file(file);
    line_t **lines = create_lines(file, content);
    int output = 0;

    my_memset(&header, 0, sizeof(header));
    if (!setup_header(lines, &header)) {
        output = 84;
    } else {
        buffer = make_instructions(lines, &(header.prog_size));
        output = write_all(file, &header, buffer);
    }
    my_free_array(content);
    my_free_array(lines);
    free(buffer);
    return (output);
}