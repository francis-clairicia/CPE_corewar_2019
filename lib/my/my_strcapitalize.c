/*
** EPITECH PROJECT, 2019
** My strcapitalize()
** File description:
** Capitalize words
*/

#include <stddef.h>

static char *cap(char *str, int i)
{
    if ((i == 0) && (str[i] >= 'a') && (str[i] <= 'z')) {
        str[i] -= 32;
        return (str);
    }
    if ((str[i] >= 'a') && (str[i] <= 'z') && (i > 0)) {
        if (((str[i - 1] < '0') || (str[i - 1] > '9')) \
            && ((str[i - 1] < 'A') || (str[i - 1] > 'Z')) \
            && ((str[i - 1] < 'a') || (str[i - 1] > 'z'))) {
            str[i] -= 32;
        }
    } else if ((str[i] >= 'A') && (str[i] <= 'Z') && (i > 0)) {
        if (((str[i - 1] >= '0') && (str[i - 1] <= '9'))
            || ((str[i - 1] >= 'a') && (str[i - 1] <= 'z'))
            || ((str[i - 1] >= 'A') && (str[i - 1] <= 'Z'))) {
            str[i] += 32;
        }
    }
    return (str);
}

char *my_strcapitalize(char *str)
{
    int i = 0;

    if (str == NULL)
        return (NULL);
    while (str[i] != '\0') {
        cap(str, i);
        i += 1;
    }
    return (str);
}
