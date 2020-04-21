/*
** EPITECH PROJECT, 2019
** my_printf
** File description:
** Recode the print function
*/

#include "my_printf.h"

static const flag_t flag_list[] = {
    {"di", &print_number},
    {"b", &print_binary},
    {"o", &print_octal},
    {"u", &print_decimal},
    {"x", &print_hexa_lower},
    {"X", &print_hexa_upper},
    {"c", &print_char},
    {"s", &print_str},
    {"S", &print_str_non_printable},
    {"p", &print_pointer},
    {NULL, NULL}
};

static int print_replacing_flag(char type, char *modifiers, va_list args)
{
    int i = 0;
    int len = 0;
    modifier_t infos = {type, my_getnbr(modifiers), ' ', 0, 0, 0, NULL};

    if (non_valid_flags(modifiers)) {
        my_putchar('%');
        my_putstr(modifiers);
        my_putchar(type);
        return (my_strlen(modifiers) + 2);
    }
    get_infos(modifiers, &infos);
    while (flag_list[i].type != NULL) {
        if (my_strchr_index(flag_list[i].type, type) >= 0)
            len = (flag_list[i].print(args, &infos));
        i += 1;
    }
    return (len);
}

static int my_printf_part2(char const *format, int *i, va_list args)
{
    char *modifiers = NULL;
    int index_save = *i;
    int n = 0;

    modifiers = get_modifiers(i, &format[*i]);
    if (format[*i] == '%' || modifiers == NULL){
        my_putchar('%');
        if (modifiers == NULL)
            *i = index_save;
        n = 1;
    } else
        n = print_replacing_flag(format[*i], modifiers, args);
    free(modifiers);
    return (n);
}

int my_vprintf(char const *format, va_list args)
{
    int i = 0;
    int nb_print = 0;

    while (format[i] != '\0') {
        if (format[i] != '%') {
            my_putchar(format[i]);
            nb_print += 1;
        } else {
            i += 1;
            nb_print += my_printf_part2(format, &i, args);
        }
        i += 1;
    }
    return (nb_print);
}

int my_printf(char const *format, ...)
{
    va_list args;
    int nb_print = 0;

    va_start(args, format);
    nb_print = my_vprintf(format, args);
    va_end(args);
    return (nb_print);
}
