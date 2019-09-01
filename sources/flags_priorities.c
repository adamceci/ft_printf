/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_priorities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceciora <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 18:47:54 by aceciora          #+#    #+#             */
/*   Updated: 2019/06/26 13:48:42 by aceciora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	flag_prio_c(t_print *datas)
{
	if (datas->preci != -1)
		datas->preci = -1;
}

void	flag_prio_x(t_print *datas)
{
	if (datas->plus_f)
		datas->plus_f = 0;
	if (datas->space_f)
		datas->space_f = 0;
}

void	flag_prio_o(t_print *datas)
{
	if (datas->space_f)
		datas->space_f = 0;
	if (datas->plus_f)
		datas->plus_f = 0;
}

void	flags_priorities(t_print *datas)
{
	if (!conv_hash_f(datas->conversion))
		datas->hash_f = 0;
	if (datas->conversion == 's' || datas->conversion == 'c' ||
			datas->conversion == 'p')
	{
		datas->plus_f = 0;
		if (datas->conversion != 'p')
			datas->zero_f = 0;
		datas->space_f = 0;
		// if (datas->conversion == 'c' || (datas->conversion == 'p' && datas->preci > 0))
		// 	datas->preci = -1;
	}
	if (numeric_conversion(datas->conversion))
	{
		if (datas->zero_f && (datas->preci != -1 || datas->minus_f))
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
		if (datas->preci == -1)
			datas->preci = 6;
	}
}
