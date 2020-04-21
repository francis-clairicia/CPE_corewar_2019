/*
** EPITECH PROJECT, 2019
** Put number
** File description:
** Display number entered as parameter
*/

int my_putchar(char c);

int my_put_nbr(long nb)
{
    if (nb < 0) {
        nb = -nb;
        my_putchar('-');
    }
    if (nb < 10) {
        my_putchar(nb + 48);
    } else {
        my_put_nbr(nb / 10);
        my_put_nbr(nb % 10);
    }
    return (0);
}
