#include "libft.h"

char *ft_lltoa_base(long long n, int base)
{
    char *str;
    int i;
    long long num;

    num = n;
    i = 0;
    while (num > 0)
    {
        i++;
        num /= base;
    }
    if (!(str = (char *)malloc(sizeof(*str) * (i + 1))))
        return (NULL);
    str[i] = '\0';
    change_base(n, base, str, i);
    return (str);
}