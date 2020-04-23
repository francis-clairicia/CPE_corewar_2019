/*
** EPITECH PROJECT, 2019
** convert_base
** File description:
** Convert a number from a base into an another
*/

#include "my_printf.h"
#include "mylist.h"

char *convert_to_base_u(unsigned long nbr, char const *base)
{
    list_t result = my_list();
    char *str_result = NULL;
    int nb_base = my_strlen(base);

    while (nbr != 0 || result.size == 0) {
        my_put_in_list(&result, base[nbr % nb_base], char);
        nbr /= nb_base;
    }
    str_result = my_list_to_str(result);
    my_free_list(&result, NULL);
    return (str_result);
}

char *convert_to_base_long(long nbr, char const *base)
{
    return (convert_to_base_u(nbr, base));
}
