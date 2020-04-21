/*
** EPITECH PROJECT, 2019
** my_showstr
** File description:
** Show string char
*/

int my_putchar(char c);

int my_putstr(char const *str);

int my_strlen(char const *str);

void convert_to_hexa(char c, char *str)
{
    int i = 0;
    char tens = '0';
    char units = '0';

    while (i < c) {
        i += 1;
        units += 1;
        if (units > 'f') {
            units = '0';
            tens += 1;
        }
        if (units == '9' + 1)
            units = 'a';
    }
    str[0] = tens;
    str[1] = units;
}

static void print_non_printable_char(char c)
{
    char str[] = "00";

    convert_to_hexa(c, str);
    my_putchar('\\');
    my_putstr(str);
}

int my_showstr(char const *str)
{
    int i = 0;
    int len = my_strlen(str);

    if (len < 0)
        return (0);
    while (i < len) {
        if (str[i] >= ' ') {
            my_putchar(str[i]);
        } else {
            print_non_printable_char(str[i]);
        }
        i += 1;
    }
    return (0);
}
