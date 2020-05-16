/*
** EPITECH PROJECT, 2019
** asm
** File description:
** test_asm_no_file.c
*/

#include <criterion/criterion.h>
#include "asm.h"

Test(asm, error_non_existing_file)
{
    char input[] = "unknown_file.s";

    cr_assert_eq(assembly(input), 84);
}

Test(asm, error_null_parameter)
{
    cr_assert_eq(assembly(NULL), 84);
}