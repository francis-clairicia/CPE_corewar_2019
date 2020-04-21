/*
** EPITECH PROJECT, 2019
** Myshowmem
** File description:
** Show a memory dump
*/

int my_putchar(char c);

int my_putstr(char const *str);

int my_strlen(char const *str);

int char_is_printable(char c);

void convert_to_hexa(char c, char *str);

static void print_string(char const *str, int min, int size)
{
    int i = min;

    while ((i < min + 16) && (i < size)) {
        if (str[i] >= ' ') {
            my_putchar(str[i]);
        } else {
            my_putchar('.');
        }
        i += 1;
    }
}

static void print_hexa(char const *str, int min, int size)
{
    int i = min;
    int j = 0;
    int space = 0;
    char hexa[] = "00";

    while ((i < min + 16) && (i < size)) {
        j += 1;
        convert_to_hexa(str[i], hexa);
        my_putstr(hexa);
        if (j % 2 == 0) {
            my_putchar(' ');
            space += 1;
        }
        i += 1;
        space += 2;
    }
    while (space < 40) {
        my_putchar(' ');
        space += 1;
    }
}

static void increase_address(char *address)
{
    int i = 6;

    address[6] += 1;
    while (i >= 0) {
        if ((address[i] > '9') && (address[i] < 'a'))
            address[i] = 'a';
        if ((address[i] > 'f') && ((i - 1) >= 0)) {
            address[i] = '0';
            address[i - 1] += 1;
        }
        i -= 1;
    }
}

int my_showmem(char const *str, int size)
{
    char address[] = "00000000";
    int i = 0;

    while (i < size) {
        my_putstr(address);
        my_putstr(":  ");
        print_hexa(str, i, size);
        print_string(str, i, size);
        my_putchar('\n');
        increase_address(address);
        i += 16;
    }
    return (0);
}
