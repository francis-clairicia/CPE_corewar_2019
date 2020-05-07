/*
** EPITECH PROJECT, 2019
** asm
** File description:
** instructions.c
*/

#include <stdlib.h>
#include "asm.h"
#include "my.h"

static void destroy_instruction_list(list_t *list)
{
    int i = 0;
    instruction_t *instruction;

    for (node_t *node = list->start; node; node = node->next) {
        instruction = NODE_DATA_PTR(node, instruction_t);
        free(instruction->label);
        for (i = 0; instruction->params[i]; i += 1)
            free(instruction->params[i]);
    }
    my_free_list(list, NULL);
}

static int get_whole_size(list_t list, int *size)
{
    *size = 0;
    for (node_t *node = list.start; node; node = node->next)
        *size += NODE_DATA_PTR(node, instruction_t)->size;
    return (*size);
}

static char *set_all_instructions_into_buffer(list_t list, int *size)
{
    char *buffer = malloc(sizeof(char) * get_whole_size(list, size));
    int start = 0;
    instruction_t *instruction;

    if (!buffer)
        return (NULL);
    for (node_t *node = list.start; node; node = node->next) {
        NODE_DATA_PTR(node, instruction_t)->address = start;
        start += NODE_DATA_PTR(node, instruction_t)->size;
    }
    for (node_t *node = list.start; node; node = node->next) {
        instruction = NODE_DATA_PTR(node, instruction_t);
        if (!add_instruction(buffer, list, *instruction)) {
            print_error(instruction->file, instruction->line->nb);
            free(buffer);
            return (NULL);
        }
    }
    return (buffer);
}

static void set_instruction_line(char const *file, line_t *line, list_t list)
{
    node_t *node = my_node(list, -1);

    if (!node)
        return;
    NODE_DATA_PTR(node, instruction_t)->line = line;
    NODE_DATA_PTR(node, instruction_t)->file = file;
}

char *make_instructions(char const *file, line_t **lines, int *size)
{
    char *buffer = NULL;
    list_t instructions = my_list();

    if (!lines || !size || !(lines[0]) || !(lines[1]) || !(lines[2]))
        return (NULL);
    for (register int i = 2; lines[i] != NULL; i += 1) {
        if (!parse_line(lines[i]->content, &instructions)) {
            destroy_instruction_list(&instructions);
            print_error(file, lines[i]->nb);
            return (NULL);
        }
        set_instruction_line(file, lines[i], instructions);
    }
    buffer = set_all_instructions_into_buffer(instructions, size);
    destroy_instruction_list(&instructions);
    return (buffer);
}