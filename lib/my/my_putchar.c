/*
** EPITECH PROJECT, 2019
** my_putchar
** File description:
** Display a character
*/

#include <unistd.h>

int my_putchar(char c)
{
    return (write(1, &c, 1) != -1);
}
