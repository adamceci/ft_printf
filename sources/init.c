/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceciora <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 18:48:05 by aceciora          #+#    #+#             */
/*   Updated: 2019/06/25 18:49:16 by aceciora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_f_ptr(char *(*f_ptr[256])(t_print *datas, va_list args))
{
	ft_bzero(f_ptr, 256);
	f_ptr[88] = &(conv_X);
	f_ptr[99] = &(conv_c);
	f_ptr[100] = &(conv_d);
	f_ptr[102] = &(conv_f);
	f_ptr[105] = &(conv_i);
	f_ptr[111] = &(conv_o);
	f_ptr[112] = &(conv_p);
	f_ptr[115] = &(conv_s);
	f_ptr[117] = &(conv_u);
	f_ptr[120] = &(conv_x);
}

void	init_vars(t_strings *solve_strs, t_print *datas)
{
	solve_strs->s1 = ft_strnew(0);
	solve_strs->s2 = NULL;
	init_f_ptr(datas->f_ptr);
	datas->modifier = NULL;
	init_struct(datas);
}

void	init_struct(t_print *datas)
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
