#include "libft.h"

unsigned int ft_power(int nb, unsigned int power)
{
    unsigned int i;
    int n;

    if (power == 0)
        return (1);
    n = nb;
    i = 1;
    while (i < power)
    {
        n *= nb;
        i++;
    }
    return (n);
}