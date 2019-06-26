/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifiers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceciora <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 18:48:08 by aceciora          #+#    #+#             */
/*   Updated: 2019/06/25 19:01:00 by aceciora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t	modifiers_d_i(t_print *datas, va_list args)
{
	intmax_t	value;

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
	else if (!ft_strcmp(datas->modifier, "j"))
		return (value = va_arg(args, intmax_t));
	else if (!ft_strcmp(datas->modifier, "z"))
		return (value = va_arg(args, ssize_t));
	return (-1);
}

uintmax_t	modifiers_o_u_x(t_print *datas, va_list args)
{
	uintmax_t	value;

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
	else if (!ft_strcmp(datas->modifier, "j"))
		return (value = va_arg(args, uintmax_t));
	else if (!ft_strcmp(datas->modifier, "z"))
		return (value = va_arg(args, size_t));
	return (-1);
}

long double	modifiers_f(t_print *datas, va_list args)
{
	long double	value;
	
	if (!datas->modifier)
		return (value = va_arg(args, double));
	else if (!ft_strcmp(datas->modifier, "l"))
		return (value = va_arg(args, double));
	else if (!ft_strcmp(datas->modifier, "L"))
		return (value = (long double)va_arg(args, double));
	return (-1);
}