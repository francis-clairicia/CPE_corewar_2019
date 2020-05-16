/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** tests_memory_error.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "corewar.h"

Test(vm, error_overlap, .init=cr_redirect_stderr)
{
    char *av[] = {"./corewar", "tests/champions/pdd.cor",
    "-a", "0", "tests/champions/abel.cor", "tests/champions/42.cor",
    "tests/champions/ebola.cor", NULL};

    cr_assert(corewar(av) == 84);
}

