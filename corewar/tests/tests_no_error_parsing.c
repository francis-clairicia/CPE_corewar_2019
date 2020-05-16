/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** tests_no_error_parsing.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "corewar.h"

Test(vm, help_flag, .init=cr_redirect_stdout)
{
    char *av[] = {"./corewar", "-h", "1", "-a", "0", "tests/champions/pdd.cor",
    "tests/champions/pdd.cor", "-dump", "0", NULL};

    cr_assert(corewar(av) == 0);
}

Test(vm, help_ac_2, .init=cr_redirect_stdout)
{
    char *av[] = {"./corewar", "-h", NULL};

    cr_assert(help(2, av) == 1);
}

Test(vm, help_ac_3, .init=cr_redirect_stdout)
{
    char *av[] = {"./corewar", "-h", NULL};

    cr_assert(help(3, av) == 0);
}