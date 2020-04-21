/*
** EPITECH PROJECT, 2019
** Square root
** File description:
** Found the square root of a number
*/

int my_pow(int nb, int p);

int my_sqrt(int nb)
{
    int sq = 0;

    if (nb <= 0)
        return (0);
    while (my_pow(sq, 2) < nb)
        sq += 1;
    if (my_pow(sq, 2) == nb)
        return (sq);
    return (sq - 1);
}
