#include "ft_printf.h"

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
    datas->neg = 0;
}