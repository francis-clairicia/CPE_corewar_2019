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
    bonus->args = NULL;
    bonus->champs = NULL;
    bonus->path_champs = ret_all_champs(&(bonus->champs));
    PCHECK(bonus->path_champs);
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
    return ret;
}