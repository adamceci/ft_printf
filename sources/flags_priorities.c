#include "ft_printf.h"

void flags_priorities(t_print *datas)
{
    if (datas->conversion == 's' || datas->conversion == 'c' ||
        datas->conversion == 'p')
    {
        datas->plus_f = 0;
        datas->hash_f = 0;
        datas->zero_f = 0;
        datas->space_f = 0;
        if (datas->conversion == 'c' || datas->conversion == 'p')
            datas->preci = -1;
    }
    if (numeric_conversion(datas->conversion))
    {
        if (datas->zero_f)
            if (datas->preci != -1 || datas->minus_f)
                datas->zero_f = 0;
        if (datas->plus_f && datas->space_f)
            datas->space_f = 0;
        if (datas->field <= datas->preci)
            datas->field = -1;
    }
    if (datas->conversion == 'f')
    {
        if (datas->plus_f && datas->space_f)
            datas->space_f = 0;
    }
}