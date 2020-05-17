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

static void print_byte(battle_t *battle, int index, champ_t *champions)
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

static int print_line(battle_t *battle, int index, champ_t *champions)
{
    my_printf("%-5X:", index);
    for (int j = 0; j < 32 && index < MEM_SIZE; j += 1, index += 1) {
        print_byte(battle, index, champions);
    }
    my_putchar('\n');
    return (index);
}

void print_dump(battle_t *battle, champ_t *champions)
{
    for (int i = 0; i < MEM_SIZE;) {
        i = print_line(battle, i, champions);
    }
}

void print_dump_graphic(battle_t *battle, champ_t *champions)
{
    int line = 0;

    for (node_t *node = battle->lines.start; node; node = node->next)
        print_line(battle, 32 * NODE_DATA(node, int), NULL);
    my_free_list(&battle->lines, NULL);
    for (champ_t *champ = champions; champ != NULL; champ = champ->next) {
        if (champ->pc != champ->former_pc &&
        !my_node_from_data(battle->pc_printed, (champ->pc % MEM_SIZE), int)) {
            line = ((champ->pc % MEM_SIZE) / 32);
            print_line(battle, 32 * line, champions);
            my_append_to_list(&battle->pc_printed, (champ->pc % MEM_SIZE), int);
        }
        print_dump_graphic(battle, champ->children);
    }
}