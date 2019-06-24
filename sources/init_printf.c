#include "ft_printf.h"

void    init_vars(t_strings *solve_strs, t_print *datas)
{
    solve_strs->s1 = ft_strnew(0);
    solve_strs->s2 = NULL;
    init_f_ptr(datas->f_ptr);
    datas->modifier = NULL;
    init_struct(datas);
}

void init_struct(t_print *datas)
{
    datas->minus_f = 0;
    datas->plus_f = 0;
    datas->hash_f = 0;
    datas->zero_f = 0;
    datas->space_f = 0;
    datas->field = -1;
    datas->preci = -1;
    datas->conversion = '0';
    if (datas->modifier)
        free(datas->modifier);
    datas->neg = 0;
}