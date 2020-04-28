/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** rev_nb.c
*/

int rev_nb(int nb)
{
    return (nb & 0x000000FF) << 24 | (nb & 0x0000FF00) << 8 |
    (nb & 0x00FF0000) >> 8 | (nb & 0xFF000000) >> 24;
}