/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** check_champ.c
*/

#include "corewar.h"
#include "mymacros.h"

static int check_champ_mem(champ_t *tmp, battle_t *battle)
{
    for (int i = 0; i < MEM_SIZE; i++) {
        if (i >= tmp->nb_address && i < tmp->nb_address +
        tmp->header->prog_size && battle->check_mem[i] == true) {
            return ret_putstr_fd(2, "Overlap detected.\n");
        } else if (i >= tmp->nb_address && i < tmp->nb_address +
        tmp->header->prog_size) {
            battle->check_mem[i] = true;
        }
    }
    return 0;
}

static int file_header(champ_t *tmp, battle_t *battle)
{
    if (fread(tmp->header, sizeof(header_t), 1, tmp->fp) != 1)
        return 84;
    if (tmp->header->magic == 0 || tmp->header->comment[0] == '\0'
    || tmp->header->prog_name[0] == '\0' || tmp->header->prog_size == 0) {
        return ret_putstr_fd(2, "Error on champ's header.\n");
    }
    tmp->header->magic = rev_nb(tmp->header->magic);
    tmp->header->prog_size = rev_nb(tmp->header->prog_size);
    if (tmp->header->magic != COREWAR_EXEC_MAGIC) {
        return ret_putstr_fd(2, "Error on the magic number.\n");
    }
    IRETURN(check_champ_mem(tmp, battle));
    return 0;
}

static void check_nb_champ_two(champ_t *champ, battle_t *battle,
                        int nb[battle->nb_champ], bool verif_nb[4])
{
    int j = 0;
    int a = 1;
    int i = 0;

    for (champ_t *tmp = champ; a <= battle->nb_champ; a++, tmp = champ) {
        for (; i != battle->nb_champ - a; i++, tmp = tmp->next);
        if (nb[i] == 0) {
            for (j = 0; j < 4 && verif_nb[j] == true; j++);
            tmp->nb_champ = j + 1;
            verif_nb[j] = true;
            nb[i] = j + 1;
        }
        i = 0;
    }
}

static int check_nb_champ(champ_t *champ, battle_t *battle)
{
    int nb[battle->nb_champ];
    int i = 0;
    bool verif_nb[4];

    my_memset(verif_nb, false, 4);
    for (champ_t *tmp = champ; tmp; tmp = tmp->next, i++) {
        nb[i] = tmp->nb_champ;
        if (nb[i] != 0 && verif_nb[nb[i] - 1] == true)
            return ret_putstr_fd(2, "double definition of prog_number.\n");
        if (nb[i] != 0)
            verif_nb[nb[i] - 1] = true;
    }
    check_nb_champ_two(champ, battle, nb, verif_nb);
    return 0;
}

int check_champ(champ_t **champ, battle_t *battle)
{
    IRETURN(check_nb_champ(*champ, battle));
    sort_champ_list(champ);
    for (champ_t *tmp = (*champ); tmp; tmp = tmp->next) {
        tmp->fp = fopen(tmp->brut_name, "r");
        if (!tmp->fp) {
            my_dprintf(2, "Can't open %s file.\n", tmp->brut_name);
            return 84;
        }
        tmp->reg[0] = tmp->nb_champ;
        IRETURN(file_header(tmp, battle));
    }
    return 0;
}