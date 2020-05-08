/*
** EPITECH PROJECT, 2019
** my_printf
** File description:
** Modifiers
*/

#include "my_printf.h"

const format_t sharp_format[] = {
    {'o', "0", 1},
    {'x', "0x", 2},
    {'X', "0X", 2}
};

static int print_sharp_format(modifier_t *infos)
{
    int i = 0;
    int len = 0;

    if (infos->sharp == 0)
        return (0);
    while (i < 3) {
        if (sharp_format[i].type == infos->type) {
            my_putstr_fd(infos->fd, sharp_format[i].format);
            len = (sharp_format[i].len);
        }
        i += 1;
    }
    return (len);
}

static int print_blank(modifier_t *infos)
{
    char space = ' ';

    if (infos->blank == 1)
        write(infos->fd, &space, 1);
    return (infos->blank);
}

static int print_sign(modifier_t *infos, char valid_char)
{
    if (infos->sign > 0 && infos->char_to_print == valid_char)
        write(infos->fd, &(infos->sign), 1);
    return (infos->sign > 0 && infos->char_to_print == valid_char);
}

int print_before(modifier_t *infos, int size_print)
{
    int i = 0;
    int len = 0;
    int sign = (infos->sign > 0);
    int blank = infos->blank;

    len += print_sharp_format(infos);
    len += print_blank(infos);
    len += print_sign(infos, '0');
    while (i + size_print + sign + blank < infos->padding) {
        write(infos->fd, &(infos->char_to_print), 1);
        i += 1;
    }
    len += print_sign(infos, ' ');
    return (len + i);
}

int print_after(modifier_t *infos, int size_print)
{
    int i = 0;
    int sign = (infos->sign > 0);
    char space = ' ';

    while (i - size_print - sign > infos->padding) {
        write(infos->fd, &space, 1);
        i -= 1;
    }
    return (-i);
}
