/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** print_dump.c
*/

#include "corewar.h"
#include "mymacros.h"

static int champion_color[] = {
    CYAN,
    GREEN,
    MAGENTA,
    YELLOW,
};

static int print_color(champ_t *champ, int i)
{
    int color = 0;

    for (champ_t *tmp = champ; tmp != NULL; tmp = tmp->next) {
        if (tmp->die == false && i == tmp->pc % MEM_SIZE)
            return (champion_color[tmp->nb_champ - 1]);
        color = print_color(champ->children, i);
        if (color != RESET)
            return (color);
    }
    return (RESET);
}

static void print_line(battle_t *battle, int index, champ_t *champions)
{
    int color = 0;

    if (battle->graphic == true) {
        color = print_color(champions, index);
        if (color != RESET) {
            my_printf(" \033[0;%dm%02X\033[0m", color, battle->mem[index]);
            return;
        }
    }
    my_printf(" %02X", battle->mem[index]);
}

void print_dump(battle_t *battle, champ_t *champions)
{
    static bool check_first = false;

    if (check_first == true)
        my_putchar('\n');
    check_first = true;
    for (int i = 0; i < MEM_SIZE;) {
        my_printf("%-5X:", i);
        for (int j = 0; j < 32; j++, i++) {
            print_line(battle, i, champions);
        }
        my_putchar('\n');
    }
}