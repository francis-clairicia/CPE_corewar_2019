/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** test_asm.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "asm.h"

void test_cor_files_indentical(char const *file_1, char const *file_2);

Test(asm, compile_an_assembly_file_into_a_cor_file)
{
    char input[] = "tests/champions/test_1.s";
    char output[] = "tests/champions/test_1.cor";
    char expected[] = "tests/output_expected/test_1.cor";

    cr_assert_eq(assembly(input), 0);
    test_cor_files_indentical(output, expected);
}

Test(asm, handle_comments)
{
    char input[] = "tests/champions/test_1_with_comments.s";
    char output[] = "tests/champions/test_1_with_comments.cor";
    char expected[] = "tests/output_expected/test_1.cor";

    cr_assert_eq(assembly(input), 0);
    test_cor_files_indentical(output, expected);
}

Test(asm, handle_empty_spaces_and_tabs)
{
    char input[] = "tests/champions/test_1_spaces_and_tabs.s";
    char output[] = "tests/champions/test_1_spaces_and_tabs.cor";
    char expected[] = "tests/output_expected/test_1.cor";

    cr_assert_eq(assembly(input), 0);
    test_cor_files_indentical(output, expected);
}

Test(asm, handle_no_extension_file)
{
    char input[] = "tests/champions/test_1_no_extension";
    char output[] = "tests/champions/test_1_no_extension.cor";
    char expected[] = "tests/output_expected/test_1.cor";

    cr_assert_eq(assembly(input), 0);
    test_cor_files_indentical(output, expected);
}

Test(asm, compile_complicated_assembly_file)
{
    char input[] = "tests/champions/test_2.s";
    char output[] = "tests/champions/test_2.cor";
    char expected[] = "tests/output_expected/test_2.cor";

    cr_assert_eq(assembly(input), 0);
    test_cor_files_indentical(output, expected);
}