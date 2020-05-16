/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** check_champs.c
*/

#include "ncurses_bonus.h"
#include "mymacros.h"

static bool my_str_endswith(char const *str, char const *to_find)
{
    int start = 0;

    if (!str || !to_find)
        return (false);
    start = my_strlen(str) - my_strlen(to_find);
    if (start < 0)
        return (false);
    return (my_strcmp(&str[start], to_find) == 0);
}

char **ret_all_champs(char ***champs)
{
    struct dirent *r_dir = NULL;
    DIR *dir = opendir("../champions");
    char **path_champs = NULL;
    char *path = "../champions/";

    PCHECK(dir);
    r_dir = readdir(dir);
    for (int i = 2; r_dir && r_dir != 0; r_dir = readdir(dir)) {
        if (r_dir->d_name[0] != '.' && my_str_endswith(r_dir->d_name, ".cor")) {
            path_champs = PREALLOC(path_champs, sizeof(char *) * (i));
            *champs = PREALLOC(*champs, sizeof(char *) * (i));
            path_champs[i - 2] = join_path(path, r_dir->d_name);
            (*champs)[i - 2] = strdup(r_dir->d_name);
            PCHECK(path_champs[i - 2] || !(*champs)[i - 2]);
            path_champs[i - 1] = NULL;
            (*champs)[i - 1] = NULL;
            i++;
        }
    } closedir(dir);
    return path_champs;
}

void your_champs(bonus_t *bonus)
{
    clear();
    mvwprintw(stdscr, 0, 0, "Your champs :");
    for (int i = 0; bonus->args && bonus->args[i]; i++) {
        if (i == 0)
            continue;
        mvwprintw(stdscr, i, 15, "%s", bonus->args[i]);
    }
    refresh();
}
