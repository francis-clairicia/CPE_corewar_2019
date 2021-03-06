/*
** EPITECH PROJECT, 2019
** asm
** File description:
** test_asm_direct_param.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "asm.h"
#include "test_macros.h"

Test(asm, error_invalid_direct_not_numeric)
{
    int size = 0;
    char *buffer = NULL;
    line_t *lines[] = {
        PTR_FIELD(line_t, "test.s", 1, ".name \"Zork\""),
        PTR_FIELD(line_t, "test.s", 2, ".comment \"Nothing\""),
        PTR_FIELD(line_t, "test.s", 3, "sti r1,%live,%1"),
        PTR_FIELD(line_t, "test.s", 4, "and r1 ,%0, r1"),
        PTR_FIELD(line_t, "test.s", 5, "live: live %1"),
        PTR_FIELD(line_t, "test.s", 6, "zjmp %:live"),
        NULL
    };

    cr_redirect_stderr();
    buffer = make_instructions(lines, &size);
    cr_assert_eq(size, 0);
    cr_assert_null(buffer);
}

Test(asm, error_invalid_direct_label_no_name)
{
    int size = 0;
    char *buffer = NULL;
    line_t *lines[] = {
        PTR_FIELD(line_t, "test.s", 1, ".name \"Zork\""),
        PTR_FIELD(line_t, "test.s", 2, ".comment \"Nothing\""),
        PTR_FIELD(line_t, "test.s", 3, "sti r1,%:,%1"),
        PTR_FIELD(line_t, "test.s", 4, "and r1 ,%0, r1"),
        PTR_FIELD(line_t, "test.s", 5, "no_live: live %1"),
        PTR_FIELD(line_t, "test.s", 6, "zjmp %:live"),
        NULL
    };

    cr_redirect_stderr();
    buffer = make_instructions(lines, &size);
    cr_assert_eq(size, 0);
    cr_assert_null(buffer);
}