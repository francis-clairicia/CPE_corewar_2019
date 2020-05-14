/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** test_vm.c
*/

#include <criterion/criterion.h>
#include <fcntl.h>
#include <stdio.h>
#include <criterion/redirect.h>
#include <zconf.h>
#include "corewar.h"

Test(vm, test_1)
{
    char *av[] = {"./corewar", "-a", "400", "tests/champions/pdd.cor",
    "-n", "4", "tests/champions/abel.cor", "tests/champions/42.cor",
    "tests/champions/ebola.cor", NULL};

    cr_assert(corewar(av) == 0);
}

Test(vm, error_overlap)
{
    char *av[] = {"./corewar", "tests/champions/pdd.cor",
    "-a", "0", "tests/champions/abel.cor", "tests/champions/42.cor",
    "tests/champions/ebola.cor", NULL};

    cr_assert(corewar(av) == 84);
}

Test(vm, error_empty_binary_zork)
{
    char *av[] = {"./corewar", "tests/champions/pdd.cor",
    "tests/champions/zork.cor", NULL};

    cr_assert(corewar(av) == 84);
}

Test(vm, error_header_bill)
{
    char *av[] = {"./corewar", "tests/champions/pdd.cor",
    "tests/champions/bill.cor", NULL};

    cr_assert(corewar(av) == 84);
}

Test(vm, error_magic_number)
{
    char *av[] = {"./corewar", "tests/champions/pdd.cor",
    "tests/champions/error_magic_number.cor", NULL};

    cr_assert(corewar(av) == 84);
}

Test(vm, double_definition_number)
{
    char *av[] = {"./corewar", "-n", "1", "tests/champions/pdd.cor",
    "-n", "1", "tests/champions/abel.cor", NULL};

    cr_assert(corewar(av) == 84);
}

Test(vm, wrong_file)
{
    char *av[] = {"./corewar", "tests/champions/wrong_file.cor",
    "tests/champions/error_magic_number.cor", NULL};

    cr_assert(corewar(av) == 84);
}

Test(vm, help_flag)
{
    char *av[] = {"./corewar", "-h", "1", "-a", "0", "tests/champions/pdd.cor",
    "tests/champions/pdd.cor", "-dump", "0", NULL};

    cr_assert(corewar(av) == 0);
}

Test(vm, dump)
{
    char *av[] = {"./corewar", "-n", "1", "-a", "0", "tests/champions/pdd.cor",
    "tests/champions/pdd.cor", "-dump", "0", NULL};

    cr_assert(corewar(av) == 0);
}

Test(vm, no_dump_appear)
{
    char *av[] = {"./corewar", "-n", "1", "-a", "0", "tests/champions/pdd.cor",
    "tests/champions/pdd.cor", "-dump", "1000000", NULL};

    cr_assert(corewar(av) == 0);
}

Test(vm, error_double_dump)
{
    char *av[] = {"./corewar", "-n", "1", "-a", "0", "tests/champions/pdd.cor",
    "tests/champions/pdd.cor", "-dump", "0", "-dump", "1", NULL};

    cr_assert(corewar(av) == 84);
}

Test(vm, error_wrong_dump)
{
    char *av[] = {"./corewar", "-n", "1", "-a", "0", "tests/champions/pdd.cor",
    "tests/champions/pdd.cor", "-dump", "a", NULL};

    cr_assert(corewar(av) == 84);
}

Test(vm, error_negative_dump)
{
    char *av[] = {"./corewar", "-n", "1", "-a", "0", "tests/champions/pdd.cor",
    "tests/champions/pdd.cor", "-dump", "-1", NULL};

    cr_assert(corewar(av) == 84);
}

Test(vm, error_double_n_flag)
{
    char *av[] = {"./corewar", "-n", "1", "-n", "2", "-a", "0",
    "tests/champions/pdd.cor", "tests/champions/pdd.cor", NULL};

    cr_assert(corewar(av) == 84);
}

Test(vm, error_wrong_n_flag)
{
    char *av[] = {"./corewar", "-n", "a", "-a", "0", "tests/champions/pdd.cor",
    "tests/champions/pdd.cor", "-dump", "a", NULL};

    cr_assert(corewar(av) == 84);
}

Test(vm, error_negative_n_flag)
{
    char *av[] = {"./corewar", "-n", "-1", "-a", "0", "tests/champions/pdd.cor",
    "tests/champions/pdd.cor", "-dump", "-1", NULL};

    cr_assert(corewar(av) == 84);
}

Test(vm, error_double_a_flag)
{
    char *av[] = {"./corewar", "-n", "1", "-a", "2", "-a", "0",
    "tests/champions/pdd.cor", "tests/champions/pdd.cor", NULL};

    cr_assert(corewar(av) == 84);
}

Test(vm, error_wrong_a_flag)
{
    char *av[] = {"./corewar", "-a", "a", "-n", "0", "tests/champions/pdd.cor",
    "tests/champions/pdd.cor", "-dump", "a", NULL};

    cr_assert(corewar(av) == 84);
}

Test(vm, error_negative_a_flag)
{
    char *av[] = {"./corewar", "-a", "-1", "-n", "0", "tests/champions/pdd.cor",
    "tests/champions/pdd.cor", "-dump", "-1", NULL};

    cr_assert(corewar(av) == 84);
}

Test(vm, error_double_g_flag)
{
    char *av[] = {"./corewar", "-g", "-g", "-a", "2", "-a", "0",
    "tests/champions/pdd.cor", "tests/champions/pdd.cor", NULL};

    cr_assert(corewar(av) == 84);
}

Test(vm, error_no_dot_cor)
{
    char *av[] = {"./corewar", "tests/champions/pdd.corr",
    "tests/champions/pdd.cor", NULL};

    cr_assert(corewar(av) == 84);
}

Test(vm, error_not_enough_champ)
{
    char *av[] = {"./corewar", "tests/champions/pdd.cor", NULL};

    cr_assert(corewar(av) == 84);
}

Test(vm, error_no_champ)
{
    char *av[] = {"./corewar", NULL};

    cr_assert(corewar(av) == 84);
}

Test(vm, error_too_much_champ)
{
    char *av[] = {"./corewar", "tests/champions/pdd.cor",
    "tests/champions/pdd.cor", "tests/champions/pdd.cor",
    "tests/champions/pdd.cor", "tests/champions/pdd.cor", NULL};

    cr_assert(corewar(av) == 84);
}

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

Test(vm, test_ldi_lldi)
{
    char *av[] = {"./corewar", "tests/champions/test_ldi.cor",
    "tests/champions/test_ldi.cor", NULL};

    cr_assert(corewar(av) == 0);
}

Test(vm, test_ld_lld)
{
    char *av[] = {"./corewar", "tests/champions/test_ld.cor",
    "tests/champions/test_ld.cor", NULL};

    cr_assert(corewar(av) == 0);
}

Test(vm, dump_graphic)
{
    char *av[] = {"./corewar", "tests/champions/test_ld.cor",
    "tests/champions/test_ld.cor", "-g", "-dump", "100", NULL};

    cr_assert(corewar(av) == 0);
}

Test(vm, help_ac_2)
{
    char *av[] = {"./corewar", "-h", NULL};

    cr_assert(help(2, av) == 1);
}

Test(vm, help_ac_3)
{
    char *av[] = {"./corewar", "-h", NULL};

    cr_assert(help(3, av) == 0);
}

Test(vm, end_graphic)
{
    char *av[] = {"./corewar", "tests/champions/test_ld.cor",
    "tests/champions/test_ld.cor", "-g", NULL};

    cr_assert(corewar(av) == 0);
}