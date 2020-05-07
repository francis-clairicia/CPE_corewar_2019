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
char *make_instructions(char const *file, line_t **lines, int *size);
void print_number_in_file(int nb, FILE *file);
void print_error(char const *file, int line);

char **read_file(char const *file);
line_t **create_lines(char **content);
bool setup_header(char * const *array, header_t *header);

/* Instruction and Parameters validation */
bool parse_line(char const *line, list_t *list);
bool valid_instruction(char const *mnemonique, int *instruction);
bool valid_parameters(char * const *parameters, int instruction);
bool valid_label(char const *label);

/* Add instruction to buffer */
typedef struct instruction
{
    char const *file;
    line_t const *line;
    char *label;
    int address;
    char code;
    bool coding_byte;
    args_type_t type[MAX_ARGS_NUMBER];
    char *params[MAX_ARGS_NUMBER];
    int size;
} instruction_t;

instruction_t init_instruction(int index, char **params, char *label);
bool add_instruction(char *buffer, list_t list, instruction_t instruction);
// Function to get the number to print
typedef int (*get_parameter_func_t)(list_t, int, char const *);
int get_register_parameter(list_t list, int address, char const *parameter);
int get_direct_parameter(list_t list, int address, char const *parameter);
int get_indirect_parameter(list_t list, int address, char const *parameter);
// Functions to add parameters in buffer
typedef void (*add_parameter_func_t)(char *, int, int *);
void add_register_parameter(char *buffer, int parameter, int *start);
void add_direct_parameter(char *buffer, int parameter, int *start);
void add_indirect_parameter(char *buffer, int parameter, int *start);

/* Utils */
char *my_strip_str(char *str, char const characters[]);

#endif /* !ASM_H_ */
