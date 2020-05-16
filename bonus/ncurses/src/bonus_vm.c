/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** bonus_vm.c
*/

#include "ncurses_bonus.h"
#include "mymacros.h"

static const scene_t scene_list[] = {
    &menu,
    &play,
    &choose_champs
};

static bonus_t *init_bonus(void)
{
    bonus_t *bonus = PMALLOC(bonus, sizeof(bonus_t));

    bonus->quit = false;
    bonus->scene = 0;
    bonus->champs = NULL;
    bonus->path_champs = ret_all_champs(&(bonus->champs));
    PCHECK(bonus->path_champs);
    bonus->args = PMALLOC(bonus->args, sizeof(char *) *
    (my_array_len(bonus->path_champs) + 1));
    bonus->args[0] = strdup("./corewar");
    for (int i = 1; i < my_array_len(bonus->path_champs) + 1; i++)
        bonus->args[i] = NULL;
    return bonus;
}

int bonus_vm(void)
{
    int ret = 0;
    bonus_t *bonus = init_bonus();

    ICHECK(bonus);
    init_ncurses();
    while (bonus->quit == false) {
        IRETURN(scene_list[bonus->scene](bonus));
    }
    endwin();
    my_free_array(bonus->champs);
    my_free_array(bonus->path_champs);
    free(bonus);
    return ret;
}