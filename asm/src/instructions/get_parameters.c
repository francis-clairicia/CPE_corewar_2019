/*
** EPITECH PROJECT, 2019
** asm
** File description:
** get_parameters.c
*/

#include "asm.h"
#include "my.h"

static instruction_t *get_instruction_by_label(list_t list, char const *label,
    errno_t *errno)
{
    instruction_t *instruction = NULL;

    for (node_t *node = list.start; node; node = node->next) {
        instruction = NODE_DATA_PTR(node, instruction_t);
        if (my_strcmp(label, instruction->label) == 0)
            return (instruction);
    }
    set_errno(errno, E_UNDEFINED_LABEL);
    return (NULL);
}

int get_register_parameter(list_t list UNUSED,
    int address UNUSED, char const *parameter, errno_t *errno UNUSED)
{
    if (!parameter)
        return (0);
    return (my_getnbr(&parameter[1]));
}

int get_direct_parameter(list_t list, int address, char const *parameter,
    errno_t *errno)
{
    int nb = 0;
    instruction_t *instruction = NULL;

    if (!parameter)
        return (0);
    if (parameter[1] != LABEL_CHAR)
        return (my_getnbr(&parameter[1]));
    instruction = get_instruction_by_label(list, &parameter[2], errno);
    if (instruction != NULL)
        nb = instruction->address - address;
    return (nb);
}

int get_indirect_parameter(list_t list, int address, char const *parameter,
    errno_t *errno)
{
    short nb = 0;
    instruction_t *instruction = NULL;

    if (!parameter)
        return (0);
    if (parameter[0] != LABEL_CHAR)
        return (my_getnbr(parameter));
    instruction = get_instruction_by_label(list, &parameter[1], errno);
    if (instruction != NULL)
        nb = instruction->address - address;
    return ((int)nb);
}