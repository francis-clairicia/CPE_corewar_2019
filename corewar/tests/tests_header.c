/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** tests_header.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "corewar.h"

Test(vm, error_header_bill, .init=cr_redirect_stderr)
{
    char *av[] = {"./corewar", "tests/champions/pdd.cor",
    "tests/champions/bill.cor", NULL};

    cr_assert(corewar(av) == 84);
}

Test(vm, error_magic_number, .init=cr_redirect_stderr)
{
    char *av[] = {"./corewar", "tests/champions/pdd.cor",
    "tests/champions/error_magic_number.cor", NULL};

    cr_assert(corewar(av) == 84);
}