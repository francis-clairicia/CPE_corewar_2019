/*
** EPITECH PROJECT, 2020
** asm
** File description:
** ASM_H_
*/

#ifndef ASM_H_
#define ASM_H_

#include <stdbool.h>
#include <stdio.h>
#include "op.h"
#include "mylist.h"
#include "my_errno.h"

typedef struct line
{
    char const *file;
    int nb;
    char const *content;
} line_t;

/* Constants */
static int const SIZE_TYPE[] = {
    [T_REG] = 1,
    [T_DIR] = DIR_SIZE,
    [T_IND] = IND_SIZE
};

static int const CODING_BYTE_DESCRIPTION_TYPE[] = {
    [T_REG] = 1,
    [T_DIR] = 2,
    [T_IND] = 3
};

#define REVERSED_NB(nb) (nb & 0x000000FFU) << 24 | (nb & 0x0000FF00U) << 8 | \
    (nb & 0x00FF0000U) >> 8 | (nb & 0xFF000000U) >> 24

int assembly(char const *file);
char *make_instructions(line_t * const *lines, int *size);
void print_number_in_file(int nb, FILE *file);
void print_error(char const *file, int line, errno_t error);

char **read_file(char const *file);
line_t **create_lines(char const *file, char **content);
bool setup_header(line_t * const *array, header_t *header);

/* Instruction and Parameters validation */
static inline char const *skip_first_spaces(char const *str)
{
    if (str != NULL) {
        while (str[0] != '\0' && (str[0] == ' ' || str[0] == '\t'))
            str = &str[1];
    }
    return (str);
}
errno_t parse_line(char const *line, list_t *list);
bool valid_instruction(char const *mnemonic, int *instruction, errno_t *err);
bool valid_parameters(char * const *parameters, int instruction, errno_t *err);
bool valid_label(char const *label, errno_t *errno);

/* Add instruction to buffer */
typedef struct instruction
{
    line_t const *line;
    char *label;
    int address;
    char code;
    bool coding_byte;
    args_type_t type[MAX_ARGS_NUMBER];
    int param_size[MAX_ARGS_NUMBER];
    char *params[MAX_ARGS_NUMBER];
    int size;
} instruction_t;

instruction_t init_instruction(int index, char **params, char *label);
errno_t add_instruction(char *buffer, list_t list, instruction_t instruction);
// Function to get the number to print
typedef int (*get_parameter_func_t)(list_t, int, char const *, errno_t *);
int get_register_parameter(list_t list, int address, char const *parameter,
    errno_t *errno);
int get_direct_parameter(list_t list, int address, char const *parameter,
    errno_t *errno);
int get_indirect_parameter(list_t list, int address, char const *parameter,
    errno_t *errno);
// Functions to add parameter in buffer
void add_parameter(char *buffer, int bytes, int size, int *start);

/* Utils */
char *my_strip_str(char *str, char const characters[]);

#endif /* !ASM_H_ */
