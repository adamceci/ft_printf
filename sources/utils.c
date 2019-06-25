#include "ft_printf.h"

int is_mod(char c)
{
    if (c == 'l' || c == 'h')
        return (1);
    return (0);
}

int numeric_conversion(char c)
{
    if (c == 'd' || c == 'i' || c == 'o' || c == 'u' || c == 'x' || c == 'X')
        return (1);
    return (0);
}

int conversion_char(char c)
{
    if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'o' ||
        c == 'u' || c == 'x' || c == 'X' || c == 'f')
        return (1);
    return (0);
}