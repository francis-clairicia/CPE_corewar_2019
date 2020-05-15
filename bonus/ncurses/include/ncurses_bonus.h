/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** ncurses_bonus.h
*/

#ifndef NCURSES_BONUS_H
#define NCURSES_BONUS_H

#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdbool.h>
#include <time.h>
#include <ncurses.h>
#include <string.h>

bool no_env(char **env);
int bonus_vm(void);
void init_game(void);
int game_loop(void);

#endif