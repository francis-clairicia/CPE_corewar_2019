/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** handle_mem.c
*/

#include "corewar.h"
#include "mymacros.h"

int fill_mem_two(champ_t *tmp, battle_t *battle)
{
    char c = '\0';
    int stock = 0;

    for (int i = tmp->nb_address; i != tmp->nb_address +
    tmp->header->prog_size; i++) {
        stock = (i >= MEM_SIZE) ? i - MEM_SIZE : i;
        if (fread(&c, sizeof(char), 1, tmp->fp) != 1)
            return ret_putstr_fd(2, "The content of the program"
            "is not consistent with this length.\n");
        battle->mem[stock] = c;
    }
    return 0;
}

int fill_mem(champ_t *champ, battle_t *battle)
{
    char c = '\0';

    for (champ_t *tmp = champ; tmp; tmp = tmp->next) {
        IRETURN(fill_mem_two(tmp, battle));
        if (fread(&c, sizeof(char), 1, tmp->fp) == 1) {
            return ret_putstr_fd(2, "The content of the program"
            "is not consistent with this length.\n");
        }
        fclose(tmp->fp);
    }
    return 0;
}

void champ_address(champ_t *champ, int nb_champ)
{
    int i = nb_champ - 1;

    for (champ_t *tmp = champ; tmp; tmp = tmp->next, i--) {
        tmp->nb_address = (tmp->nb_address != -1) ? tmp->nb_address :
        (i * MEM_SIZE / nb_champ) % MEM_SIZE;
    }
}