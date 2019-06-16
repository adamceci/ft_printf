#include "libft.h"

char *ft_lltoa(long long n)
{
    char *str;
    int nb_chars;
    int i;

    nb_chars = ft_count_chars(n);
    if (!(str = ft_strnew(nb_chars)))
        return (NULL);
    i = nb_chars - 1;
    while (i >= 0)
    {
        str[i] = ft_fill_char(str, &n);
        i--;
    }
    return (str);
}