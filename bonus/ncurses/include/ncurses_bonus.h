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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct bonus_s
{
    int scene;
    bool quit;
    char **args;
    char **path_champs;
    char **champs;
} bonus_t;

typedef struct window_s
{
    int x;
    int y;
    WINDOW *window;
} window_t;

typedef int (*scene_t)(bonus_t *);
int menu(bonus_t *bonus);
int play(bonus_t *bonus);
int choose_champs(bonus_t *bonus);
window_t create_window(void);

bool no_env(char **env);
int bonus_vm(void);
void init_ncurses(void);
char **ret_all_champs(char ***champs);

#endif