/*
** EPITECH PROJECT, 2019
** asm
** File description:
** valid_parameters.c
*/

#include "asm.h"
#include "my.h"

static bool valid_register_parameter(char const *parameter)
{
    int nbr = 0;

    if (!my_str_isnum(&parameter[1]))
        return (set_errno(E_INVALID_REGISTER));
    nbr = my_getnbr(&parameter[1]);
    if (nbr < 1 || nbr > REG_NUMBER)
        return (set_errno(E_INVALID_REGISTER));
    return (true);
}

static bool valid_direct_parameter(char const *parameter)
{
    if (parameter[1] == LABEL_CHAR) {
        if (parameter[2] == '\0')
            return (set_errno(E_UNDEFINED_LABEL));
    } else if (!my_str_isnum(&parameter[1]))
        return (set_errno(E_INVALID_ARG));
    return (true);
}

static bool valid_indirect_parameter(char const *parameter)
{
    return (my_str_isnum(parameter));
}

static bool valid_one_parameter(char const *parameter, char type)
{
    if ((type & T_REG) && parameter[0] == 'r')
        return (valid_register_parameter(parameter));
    if ((type & T_DIR) && parameter[0] == DIRECT_CHAR)
        return (valid_direct_parameter(parameter));
    if ((type & T_IND))
        return (valid_indirect_parameter(parameter));
    return (set_errno(E_INVALID_ARG));
}

bool valid_parameters(char * const *parameters, int instruction)
{
    op_t *operation = &op_tab[instruction];

    if (parameters == NULL || my_array_len(parameters) != operation->nbr_args)
        return (set_errno(E_INVALID_ARG));
    for (int i = 0; parameters[i] != NULL; i += 1) {
        my_strip_str(parameters[i], " ");
        if (!valid_one_parameter(parameters[i], operation->type[i]))
            return (false);
    }
    return (set_errno(E_SUCCESS));
}