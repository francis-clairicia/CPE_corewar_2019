/*
** EPITECH PROJECT, 2020
** mnemonic sub
** File description:
** corewar
*/

#include "corewar.h"
#include "mymacros.h"

int mne_sub(champ_t *champ, battle_t *battle)
{
    int *param = get_param_type(battle->mem[(champ->pc + 1) % MEM_SIZE]);
    int fst_param = battle->mem[(champ->pc + 2) % MEM_SIZE];
    int scd_param = battle->mem[(champ->pc + 3) % MEM_SIZE];
    int thd_param = battle->mem[(champ->pc + 4) % MEM_SIZE];

    ICHECK(param);
    if (param[0] != T_REG || param[1] != T_REG || param[2] != T_REG) {
        champ->pc += 1;
        free(param);
        return 0;
    }
    if (is_register(fst_param) && is_register(fst_param)
    && is_register(thd_param)) {
        champ->reg[thd_param - 1] = champ->reg[fst_param - 1]
        - champ->reg[scd_param - 1];
        champ->carry = (champ->reg[thd_param - 1] == 0) ? 1 : 0;
    }
    champ->pc += 5;
    free(param);
    return 0;
}