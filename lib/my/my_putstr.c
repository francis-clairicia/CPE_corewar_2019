/*
** EPITECH PROJECT, 2019
** My put str
** File description:
** Display a string
*/

#include <unistd.h>
#include <stddef.h>

int my_strlen(char const *str);

int my_putstr_fd(int fd, char const *str)
{
    if (fd < 0)
        return (0);
    if (str == NULL)
        return (my_putstr_fd(fd, "NULL"));
    return (write(fd, str, my_strlen(str)) != -1);
}

int my_putstr(char const *str)
{
    return (my_putstr_fd(1, str));
}

int my_putstr_error(char const *str)
{
    return (my_putstr_fd(2, str));
}