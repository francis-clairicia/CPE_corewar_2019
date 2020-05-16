/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** tests_error_parsing.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "corewar.h"

Test(vm, double_definition_number, .init=cr_redirect_stderr)
{
    char *av[] = {"./corewar", "-n", "1", "tests/champions/pdd.cor",
    "-n", "1", "tests/champions/abel.cor", NULL};

    cr_assert(corewar(av) == 84);
}

Test(vm, error_double_dump, .init=cr_redirect_stderr)
{
    char *av[] = {"./corewar", "-n", "1", "-a", "0", "tests/champions/pdd.cor",
    "tests/champions/pdd.cor", "-dump", "0", "-dump", "1", NULL};

    cr_assert(corewar(av) == 84);
}

Test(vm, error_wrong_dump, .init=cr_redirect_stderr)
{
    char *av[] = {"./corewar", "-n", "1", "-a", "0", "tests/champions/pdd.cor",
    "tests/champions/pdd.cor", "-dump", "a", NULL};

    cr_assert(corewar(av) == 84);
}

Test(vm, error_negative_dump, .init=cr_redirect_stderr)
{
    char *av[] = {"./corewar", "-n", "1", "-a", "0", "tests/champions/pdd.cor",
    "tests/champions/pdd.cor", "-dump", "-1", NULL};

    cr_assert(corewar(av) == 84);
}

Test(vm, error_double_n_flag, .init=cr_redirect_stderr)
{
    char *av[] = {"./corewar", "-n", "1", "-n", "2", "-a", "0",
    "tests/champions/pdd.cor", "tests/champions/pdd.cor", NULL};

    cr_assert(corewar(av) == 84);
}

Test(vm, error_wrong_n_flag, .init=cr_redirect_stderr)
{
    char *av[] = {"./corewar", "-n", "a", "-a", "0", "tests/champions/pdd.cor",
    "tests/champions/pdd.cor", "-dump", "a", NULL};

    cr_assert(corewar(av) == 84);
}

Test(vm, error_negative_n_flag, .init=cr_redirect_stderr)
{
    char *av[] = {"./corewar", "-n", "-1", "-a", "0", "tests/champions/pdd.cor",
    "tests/champions/pdd.cor", "-dump", "-1", NULL};

    cr_assert(corewar(av) == 84);
}

Test(vm, error_double_a_flag, .init=cr_redirect_stderr)
{
    char *av[] = {"./corewar", "-n", "1", "-a", "2", "-a", "0",
    "tests/champions/pdd.cor", "tests/champions/pdd.cor", NULL};

    cr_assert(corewar(av) == 84);
}

Test(vm, error_wrong_a_flag, .init=cr_redirect_stderr)
{
    char *av[] = {"./corewar", "-a", "a", "-n", "0", "tests/champions/pdd.cor",
    "tests/champions/pdd.cor", "-dump", "a", NULL};

    cr_assert(corewar(av) == 84);
}

Test(vm, error_negative_a_flag, .init=cr_redirect_stderr)
{
    char *av[] = {"./corewar", "-a", "-1", "-n", "0", "tests/champions/pdd.cor",
    "tests/champions/pdd.cor", "-dump", "-1", NULL};

    cr_assert(corewar(av) == 84);
}

Test(vm, error_double_g_flag, .init=cr_redirect_stderr)
{
    char *av[] = {"./corewar", "-g", "-g", "-a", "2", "-a", "0",
    "tests/champions/pdd.cor", "tests/champions/pdd.cor", NULL};

    cr_assert(corewar(av) == 84);
}

Test(vm, error_no_dot_cor, .init=cr_redirect_stderr)
{
    char *av[] = {"./corewar", "tests/champions/pdd.corr",
    "tests/champions/pdd.cor", NULL};

    cr_assert(corewar(av) == 84);
}

Test(vm, error_not_enough_champ, .init=cr_redirect_stderr)
{
    char *av[] = {"./corewar", "tests/champions/pdd.cor", NULL};

    cr_assert(corewar(av) == 84);
}

Test(vm, error_no_champ, .init=cr_redirect_stderr)
{
    char *av[] = {"./corewar", NULL};

    cr_assert(corewar(av) == 84);
}

Test(vm, error_too_much_champ, .init=cr_redirect_stderr)
{
    char *av[] = {"./corewar", "tests/champions/pdd.cor",
    "tests/champions/pdd.cor", "tests/champions/pdd.cor",
    "tests/champions/pdd.cor", "tests/champions/pdd.cor", NULL};

    cr_assert(corewar(av) == 84);
}