/*
** EPITECH PROJECT, 2019
** asm
** File description:
** init_instruction.c
*/

#include "asm.h"
#include "my.h"

static char * const no_coding_byte[] = {
    "live",
    "zjmp",
    "fork",
    "lfork",
    NULL
};

static char * const two_bytes_direct_param[] = {
    "zjmp",
    "sti",
    "ldi",
    "lldi",
    "fork",
    "lfork",
    NULL
};

static args_type_t get_parameter_type(char const *parameter)
{
    if (parameter[0] == 'r')
        return (T_REG);
    if (parameter[0] == DIRECT_CHAR)
        return (T_DIR);
    return (T_IND);
}

static void get_parameter_size(instruction_t *instruction, int param_index,
    char const *mnemonic)
{
    int type = instruction->type[param_index];

    if (type == T_DIR && my_array_contains(two_bytes_direct_param, mnemonic))
        instruction->param_size[param_index] = SIZE_TYPE[T_IND];
    else
        instruction->param_size[param_index] = SIZE_TYPE[type];
}

instruction_t init_instruction(int index, char **params, char *label)
{
    instruction_t instruction;
    char *command = op_tab[index].mnemonic;

    my_memset(&instruction, 0, sizeof(instruction));
    instruction.label = label;
    if (index >= 0) {
        instruction.code = op_tab[index].code;
        instruction.size += sizeof(instruction.code);
        instruction.coding_byte = !my_array_contains(no_coding_byte, command);
        instruction.size += (instruction.coding_byte != false);
        for (int i = 0; params && params[i] != NULL; i += 1) {
            instruction.params[i] = params[i];
            instruction.type[i] = get_parameter_type(params[i]);
            get_parameter_size(&instruction, i, command);
            instruction.size += instruction.param_size[i];
        }
        free(params);
    }
    return (instruction);
}