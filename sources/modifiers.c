#include "ft_printf.h"

intmax_t    modifiers_d_i(t_print *datas, va_list args)
{
    intmax_t   value;

    if (!datas->modifier)
        return (value = va_arg(args, int));
    else if (!ft_strcmp(datas->modifier, "hh"))
        return (value = (signed char)va_arg(args, int));
    else if (!ft_strcmp(datas->modifier, "h"))
        return (value = (short)va_arg(args, int));
    else if (!ft_strcmp(datas->modifier, "l"))
        return (value = va_arg(args, long));
    else if (!ft_strcmp(datas->modifier, "ll"))
        return (value = va_arg(args, long long));
    return (0); // faire un exit ?
}

uintmax_t   modifiers_o_u_x(t_print * datas, va_list args)
{
    uintmax_t   value;
    
    if (!datas->modifier)
        return (value = va_arg(args, unsigned int));
    else if (!ft_strcmp(datas->modifier, "hh"))
        return (value = (unsigned char)va_arg(args, unsigned int));
    else if (!ft_strcmp(datas->modifier, "h"))
        return (value = (unsigned short)va_arg(args, unsigned int));
    else if (!ft_strcmp(datas->modifier, "l"))
        return (value = va_arg(args, unsigned long));
    else if (!ft_strcmp(datas->modifier, "ll"))
        return (value = va_arg(args, unsigned long long));
    return (0); // faire un exit ?
}