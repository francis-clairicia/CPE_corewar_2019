/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** tests_header.c
*/

#include <criterion/criterion.h>
#include "corewar.h"

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