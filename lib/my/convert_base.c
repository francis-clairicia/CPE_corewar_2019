/*
** EPITECH PROJECT, 2019
** convert_base
** File description:
** Convert a number from a base into an another
*/

#include "my.h"
#include "list/mylist.h"

char *convert_to_base(int nbr, char const *base)
{
    list_t result = my_list();
    char *str_result = NULL;
    int nb_base = my_strlen(base);
    int negative_result = (nbr < 0);

    if (nbr < 0)
        nbr = -nbr;
    while (nbr != 0 || result.size == 0) {
        my_put_in_list(&result, base[nbr % nb_base], char);
        nbr /= nb_base;
    }
    if (negative_result)
        my_put_in_list(&result, '-', char);
    str_result = my_list_to_str(result);
    my_free_list(&result, NULL);
    return (str_result);
}

char *convert_base(char const *nbr, char const *base_from, char const *base_to)
{
    int nbr_base_10 = my_getnbr_base(nbr, base_from);
    char *nbr_converted = convert_to_base(nbr_base_10, base_to);

    return (nbr_converted);
}
