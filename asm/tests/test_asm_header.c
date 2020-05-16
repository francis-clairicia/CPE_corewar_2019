/*
** EPITECH PROJECT, 2019
** asm
** File description:
** test_asm_header.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "asm.h"

Test(asm, error_for_no_header)
{
    char *input[] = {
        "tests/champions/test_header_1_no_name_and_comment.s",
        "tests/champions/test_header_1_empty_file.s",
    };

    cr_redirect_stderr();
    for (size_t i = 0; i < sizeof(input) / sizeof(input[0]); i += 1)
        cr_assert_eq(assembly(input[i]), 84);
}

Test(asm, error_header_comment_comes_before_name)
{
    char input[] = "tests/champions/test_header_2.s";

    cr_redirect_stderr();
    cr_assert_eq(assembly(input), 84);
}

Test(asm, error_header_invalid_syntax_values)
{
    char *input[] = {
        "tests/champions/test_header_3_no_quotes.s",
        "tests/champions/test_header_3_one_quote_at_start.s",
        "tests/champions/test_header_3_one_quote_at_end.s",
        "tests/champions/test_header_3_word_before_quote.s",
        "tests/champions/test_header_3_word_after_last_quote.s",
        "tests/champions/test_header_3_invalid_instruction.s",
    };

    cr_redirect_stderr();
    for (size_t i = 0; i < sizeof(input) / sizeof(input[0]); i += 1)
        cr_assert_eq(assembly(input[i]), 84);
}