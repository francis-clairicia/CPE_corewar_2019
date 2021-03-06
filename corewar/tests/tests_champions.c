/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** tests_champions.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "corewar.h"

Test(vm, test_1, .init=cr_redirect_stdout)
{
    char *av[] = {"./corewar", "-a", "400", "tests/champions/pdd.cor",
    "-n", "4", "tests/champions/abel.cor", "tests/champions/42.cor",
    "tests/champions/ebola.cor", NULL};

    cr_assert(corewar(av) == 0);
}

Test(vm, test_ldi_lldi, .init=cr_redirect_stdout)
{
    char *av[] = {"./corewar", "tests/champions/test_ldi.cor",
    "tests/champions/test_ldi.cor", NULL};

    cr_assert(corewar(av) == 0);
}

Test(vm, test_ld_lld, .init=cr_redirect_stdout)
{
    char *av[] = {"./corewar", "tests/champions/test_ld.cor",
    "tests/champions/test_ld.cor", NULL};

    cr_assert(corewar(av) == 0);
}

Test(vm, error_empty_binary_zork, .init=cr_redirect_stderr)
{
    char *av[] = {"./corewar", "tests/champions/pdd.cor",
    "tests/champions/zork.cor", NULL};

    cr_assert(corewar(av) == 84);
}

Test(vm, wrong_file, .init=cr_redirect_stderr)
{
    char *av[] = {"./corewar", "tests/champions/wrong_file.cor",
    "tests/champions/error_magic_number.cor", NULL};

    cr_assert(corewar(av) == 84);
}