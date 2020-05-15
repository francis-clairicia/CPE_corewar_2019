/*
** EPITECH PROJECT, 2019
** asm
** File description:
** valid_parameters.c
*/

#include "asm.h"
#include "my.h"

static bool valid_register_parameter(char const *parameter, errno_t *err)
{
    int nbr = 0;

    if (!my_str_isnum(&parameter[1]))
        return (set_errno(err, E_INVALID_REGISTER));
    nbr = my_getnbr(&parameter[1]);
    if (nbr < 1 || nbr > REG_NUMBER)
        return (set_errno(err, E_INVALID_REGISTER));
    return (true);
}

static bool valid_direct_parameter(char const *parameter, errno_t *err)
{
    if (parameter[1] == LABEL_CHAR) {
        if (parameter[2] == '\0')
            return (set_errno(err, E_UNDEFINED_LABEL));
    } else if (!my_str_isnum(&parameter[1]))
        return (set_errno(err, E_INVALID_ARG));
    return (true);
}

static bool valid_indirect_parameter(char const *parameter, errno_t *err)
{
    if (parameter[0] == LABEL_CHAR) {
        if (parameter[1] == '\0')
            return (set_errno(err, E_UNDEFINED_LABEL));
    } else if (!my_str_isnum(parameter))
        return (set_errno(err, E_INVALID_ARG));
    return (true);
}

static bool valid_one_parameter(char const *parameter, char type, errno_t *err)
{
    if ((type & T_REG) && parameter[0] == 'r')
        return (valid_register_parameter(parameter, err));
    if ((type & T_DIR) && parameter[0] == DIRECT_CHAR)
        return (valid_direct_parameter(parameter, err));
    if ((type & T_IND))
        return (valid_indirect_parameter(parameter, err));
    return (set_errno(err, E_INVALID_ARG));
}

bool valid_parameters(char * const *parameters, int instruction, errno_t *err)
{
    op_t *operation = &op_tab[instruction];

    if (parameters == NULL || my_array_len(parameters) != operation->nbr_args)
        return (set_errno(err, E_INVALID_ARG));
    for (int i = 0; parameters[i] != NULL; i += 1) {
        my_strip_str(parameters[i], " \t");
        if (!valid_one_parameter(parameters[i], operation->type[i], err))
            return (false);
    }
    return (set_errno(err, E_SUCCESS));
}