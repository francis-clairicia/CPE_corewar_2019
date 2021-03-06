/*
** EPITECH PROJECT, 2019
** asm
** File description:
** add_instruction.c
*/

#include "asm.h"

static const get_parameter_func_t get_parameter[] = {
    [T_REG] = get_register_parameter,
    [T_DIR] = get_direct_parameter,
    [T_IND] = get_indirect_parameter
};

static void set_coding_byte(char *buffer,
    instruction_t *instruction, int *start)
{
    int type = 0;
    char coding_byte = 0;

    if (instruction->coding_byte == false)
        return;
    for (int i = 0; instruction->params[i] != NULL; i += 1) {
        type = instruction->type[i];
        coding_byte |= (CODING_BYTE_DESCRIPTION_TYPE[type] << ((3 - i) * 2));
    }
    buffer[*start] = coding_byte;
    *start += 1;
}

static void set_code(char *buffer, instruction_t *instruction, int *start)
{
    buffer[*start] = instruction->code;
    *start += 1;
    set_coding_byte(buffer, instruction, start);
}

errno_t add_instruction(char *buffer, list_t list, instruction_t instruction)
{
    int addr = instruction.address;
    int start = addr;
    int type = 0;
    long parameter = 0;
    errno_t errno = E_SUCCESS;
    char *param = NULL;

    if (!buffer)
        return (E_INTERNAL_ERROR);
    set_code(buffer, &instruction, &start);
    for (int i = 0; instruction.params[i] != NULL; i += 1) {
        type = instruction.type[i];
        param = instruction.params[i];
        parameter = get_parameter[type](list, addr, param, &errno);
        if (errno != E_SUCCESS)
            break;
        add_parameter(buffer, parameter, instruction.param_size[i], &start);
    }
    return (errno);
}