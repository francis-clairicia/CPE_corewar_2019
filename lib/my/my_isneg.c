/*
** EPITECH PROJECT, 2019
** My is neg
** File description:
** Know if a interger are negative or positive
*/

#include <my.h>

int my_isneg(int n)
{
    if (n < 0) {
        my_putchar('N');
    } else {
        my_putchar('P');
    }
    my_putchar('\n');
    return (0);
}
