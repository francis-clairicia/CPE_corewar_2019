/*
** EPITECH PROJECT, 2019
** PSU_my_printf_2019
** File description:
** my_printf_infos.c
*/

#include "my_printf.h"

static void check_sharp(char *mod, int i, modifier_t *infos)
{
    if (mod[i] == '#' && my_strchr_index("oxX", infos->type) >= 0)
        infos->sharp = 1;
}

static void check_padding(char *mod, int i, modifier_t *infos)
{
    if ((((mod[i] == '0' && my_strchr_index(mod, '-') == -1))
    || (mod[i] == '.')) && infos->char_to_print == ' ') {
        infos->char_to_print = '0';
        infos->padding = my_getnbr(&mod[i + 1]);
    }
    if (mod[i] == '-' && my_strchr_index("123456789", mod[i + 1]) >= 0)
        infos->padding = my_getnbr(&mod[i]);
}

static void check_plus(char *mod, int i, modifier_t *infos)
{
    if (mod[i] == '+' && my_strchr_index("di", infos->type) >= 0)
        infos->sign = 1;
}

static void check_blank(char *mod, int i, modifier_t *infos)
{
    if (infos->blank == 0 && mod[i] == ' '
    && my_strchr_index("di", infos->type) >= 0)
        infos->blank = 1;
}

void get_infos(char *modifiers, modifier_t *infos)
{
    int i = 0;

    while (modifiers[i] != '\0' && my_strchr_index("lhq", modifiers[i]) == -1) {
        check_sharp(modifiers, i, infos);
        check_padding(modifiers, i, infos);
        check_plus(modifiers, i, infos);
        check_blank(modifiers, i, infos);
        i += 1;
    }
    infos->length_modifier = &modifiers[i];
}