/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** check_champ.c
*/

#include "corewar.h"
#include "macro.h"

static int file_header(champ_t *tmp)
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
    printf("%d   %d\n", tmp->header->magic, tmp->header->prog_size);
    return 0;
}

int check_champ(champ_t **champ)
{
    sort_champ_list(champ);
    for (champ_t *tmp = (*champ); tmp; tmp = tmp->next) {
        tmp->fp = fopen(tmp->brut_name, "r");
        if (!tmp->fp) {
            my_dprintf(2, "Can't open %s file.\n", tmp->brut_name);
            return 84;
        }
        IRETURN(file_header(tmp));
    }
    return 0;
}