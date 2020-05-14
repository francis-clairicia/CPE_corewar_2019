/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** tests_memory_no_error.c
*/

#include <criterion/criterion.h>
#include "corewar.h"

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

Test(vm, dump_graphic)
{
    char *av[] = {"./corewar", "tests/champions/test_ld.cor",
    "tests/champions/test_ld.cor", "-g", "-dump", "100", NULL};

    cr_assert(corewar(av) == 0);
}

Test(vm, end_graphic)
{
    char *av[] = {"./corewar", "tests/champions/test_ld.cor",
    "tests/champions/test_ld.cor", "-g", NULL};

    cr_assert(corewar(av) == 0);
}