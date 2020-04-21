/*
** EPITECH PROJECT, 2019
** Is prime
** File description:
** Verify if a number is prime
*/

int my_is_prime(int nb)
{
    int denominateur = 2;
    int result;

    if (nb <= 1)
        return (0);
    while (denominateur < nb - 1) {
        result = nb / denominateur;
        if (result * denominateur == nb)
            return (0);
        denominateur += 1;
    }
    return (1);
}
