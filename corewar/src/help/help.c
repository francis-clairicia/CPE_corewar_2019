/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** help.c
*/

#include "my.h"

void print_help(int syntax)
{
    if (syntax == 2)
        my_putstr_fd(syntax, "Syntax Error\n\n");
    my_putstr_fd(syntax, "USAGE\n");
    my_putstr_fd(syntax, "\t./corewar [-g] [-dump nbr_cycle] [[-n prog_number]"
    " [-a load_address] prog_name] ...\n");
    if (syntax == 2)
        return;
    my_putstr_fd(syntax, "\nDESCRIPTION\n");
    my_putstr_fd(syntax, "\t-dump nbr_cycle dumps the memory after the "
    "nbr_cycle execution (if the round isn't\n\t\t\talready over) with the "
    "following format: 32 bytes/line in\n\t\t\thexadecimal "
    "(A0BCDEFE1DD3...)\n");
    my_putstr_fd(syntax, "\t-n prog_number  sets the next program's number. "
    "By default, the first free number\n\t\t\tin the parameter order\n");
    my_putstr_fd(syntax, "\t-a load_address sets the next program's loading "
    "address. When no address is\n\t\t\tspecified, optimize the addresses so "
    "that the processes are as far\n\t\t\taway from each other as possible."
    " The addresses are MEM_SIZE modulo\n");
}

int help(int ac, char **av)
{
    if (ac == 2 && my_strcmp(av[1], "-h") == 0) {
        print_help(1);
        return 1;
    }
    return 0;
}