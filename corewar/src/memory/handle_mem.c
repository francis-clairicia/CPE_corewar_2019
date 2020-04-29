/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** handle_mem.c
*/

#include "corewar.h"
#include "mymacros.h"

int fill_mem(champ_t *champ, battle_t *battle)
{
    char c = '\0';
    int stock = 0;

    for (champ_t *tmp = champ; tmp; tmp = tmp->next) {
        for (int i = tmp->nb_address; i != tmp->nb_address +
        tmp->header->prog_size; i++) {
            stock = (i >= MEM_SIZE) ? i - MEM_SIZE : i;
            if (fread(&c, sizeof(char), 1, tmp->fp) != 1)
                return ret_putstr_fd(2, "The content of the program"
                "is not consistent with this length.\n");
            battle->mem[stock] = c;
        }
        if (fread(&c, sizeof(char), 1, tmp->fp) == 1) {
            return ret_putstr_fd(2, "The content of the program"
            "is not consistent with this length.\n");
        }
        fclose(tmp->fp);
    }
    return 0;
}