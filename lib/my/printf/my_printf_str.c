/*
** EPITECH PROJECT, 2019
** my_printf
** File description:
** Recode the print function
*/

#include <unistd.h>
#include "my_printf.h"

static int get_str_size(char const *str)
{
    int i = 0;
    int len = 0;

    if (str == NULL)
        return (my_strlen("(null)"));
    while (str[i] != '\0') {
        if (str[i] < 32 || str[i] >= 127)
            len += 4;
        else
            len += 1;
        i += 1;
    }
    return (len);
}

int print_char(va_list args, modifier_t *infos)
{
    int len = 0;
    unsigned char c = va_arg(args, int);

    len += print_before(infos, 1);
    len += write(1, &c, 1);
    len += print_after(infos, 1);
    return (len);
}

int print_str(va_list args, modifier_t *infos)
{
    int len = 0;
    char *str = va_arg(args, char *);
    int size = get_str_size(str);

    len += print_before(infos, size);
    my_putstr(str);
    len += print_after(infos, size);
    return (size + len);
}

int print_str_non_printable(va_list args, modifier_t *infos)
{
    char *str = va_arg(args, char *);
    int len = 0;
    int i = 0;
    int size = get_str_size(str);

    len += print_before(infos, size);
    if (str == NULL) {
        my_putstr(NULL);
        len += print_after(infos, size);
        return (len + size);
    } while (str[i] != '\0') {
        if (str[i] < 32 || str[i] >= 127)
            my_printf("\\%.3o", str[i]);
        else
            my_putchar(str[i]);
        i += 1;
    }
    len += print_after(infos, size);
    return (len + size);
}
