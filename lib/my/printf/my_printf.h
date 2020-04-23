/*
** EPITECH PROJECT, 2019
** my_printf Header
** File description:
** Header for my_printf()
*/


#ifndef HEADER_MY_PRINTF
#define HEADER_MY_PRINTF

#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include "my.h"

typedef struct format
{
    char type;
    char *format;
    int len;
} format_t;

typedef struct modifier_s
{
    char type;
    int padding;
    char char_to_print;
    int sharp;
    char sign;
    int blank;
    char *length_modifier;
} modifier_t;

typedef struct flag_s
{
    char *type;
    int (*print)(va_list , modifier_t *);
} flag_t;

int my_printf(char const *format, ...);
int my_vprintf(char const *format, va_list ap);
int print_number(va_list args, modifier_t *infos);
int print_binary(va_list args, modifier_t *infos);
int print_octal(va_list args, modifier_t *infos);
int print_hexa_lower(va_list args, modifier_t *infos);
int print_hexa_upper(va_list args, modifier_t *infos);
int print_decimal(va_list args, modifier_t *infos);
int print_char(va_list args, modifier_t *infos);
int print_str(va_list args, modifier_t *infos);
int print_str_non_printable(va_list args, modifier_t *infos);
int print_pointer(va_list args, modifier_t *infos);
int print_before(modifier_t *infos, int size_print);
int print_after(modifier_t *infos, int size_print);
char *convert_to_base_u(unsigned long nb, char const *base);
char *convert_to_base_long(long nb, char const *base);
int my_putnbr_base_u(unsigned long nb, modifier_t *infos, char const *base);
int my_putnbr_long(long nb, modifier_t *infos);
int my_nbr_len_u(unsigned long nb);
char *get_modifiers(int *i, char const *str);
int non_valid_flags(char const *mod);
int non_valid_length_modifier(char const *str);
void get_infos(char *modifiers, modifier_t *infos);

#endif
