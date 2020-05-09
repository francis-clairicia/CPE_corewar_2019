/*
** EPITECH PROJECT, 2020
** mnemonic aff
** File description:
** corewar
*/

#include "corewar.h"

int mne_aff(champ_t *chp, battle_t *bat)
{
    int param[4] = get_param_type(&param, bat->mem[(chp->pc + 1) % MEM_SIZE]);
    int fst_param = bat->mem[(chp->pc + 2) % MEM_SIZE];
    int value_to_print = 0;

    if (param[0] != T_REG) {
        chp->pc += 3;
        return 0;
    }
    if (is_register(fst_param) == 1) {
        value_to_print = chp->reg[fst_param - 1] % 256;
        my_putchar(value_to_print);
        chp->pc += 3;
    }
    return 0;
}