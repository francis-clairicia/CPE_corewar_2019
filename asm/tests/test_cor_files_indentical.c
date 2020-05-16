/*
** EPITECH PROJECT, 2019
** asm
** File description:
** test_cor_files_indentical.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>

void test_cor_files_indentical(char const *file_1, char const *file_2)
{
    FILE *fp_file_1 = NULL;
    FILE *fp_file_2 = NULL;

    if (!file_1 || !file_2)
        cr_assert_fail("Files given are invalid");
    fp_file_1 = fopen(file_1, "rb");
    fp_file_2 = fopen(file_2, "rb");
    if (!fp_file_1 || !fp_file_2) {
        if (fp_file_1)
            fclose(fp_file_1);
        if (fp_file_2)
            fclose(fp_file_2);
        cr_assert_fail("Can't open the files for the tests");
    }
    cr_expect_file_contents_eq(fp_file_1, fp_file_2, "Binary .cor differs");
    fclose(fp_file_1);
    fclose(fp_file_2);
}