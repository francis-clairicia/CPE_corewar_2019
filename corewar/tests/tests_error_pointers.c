/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** tests_error_pointers.c
*/

#include <criterion/criterion.h>
#include "corewar.h"

Test(vm, error_pointer_get_param_type)
{
    param_t *params = NULL;
    unsigned char a = 'a';

    get_param_type(params, a);
    cr_assert(params == NULL);
}

Test(vm, error_pointer_valid_params)
{
    cr_assert(valid_params(NULL, 0) == false);
}

Test(vm, error_pointer_set_params_values_without_cb)
{
    cr_assert(set_param_values_without_cb(NULL, NULL, 0, NULL) == 0);
}

Test(vm, error_pointer_add_parameter)
{
    unsigned char *buffer = NULL;
    add_parameter(buffer, 0, 0, 0);
    cr_assert(buffer == NULL);
}

Test(vm, add_parameter_start_negative)
{
    unsigned char *buffer = NULL;
    add_parameter(buffer, 0, 0, -1);
    cr_assert(buffer == NULL);
}