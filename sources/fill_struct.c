/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceciora <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 18:47:39 by aceciora          #+#    #+#             */
/*   Updated: 2019/06/25 19:00:26 by aceciora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_mod(t_print *datas, char *str, int *i)
{
	if (str[*i + 1] == str[*i])
	{
		datas->modifier = ft_strnew(2);
		datas->modifier[0] = str[*i];
		datas->modifier[1] = str[*i + 1];
		(*i)++;
	}
	else
	{
		datas->modifier = ft_strnew(1);
		datas->modifier[0] = str[*i];
	}
}

void	fill_data(char *str, int *i, t_print *datas)
{
	if (str[*i] == '-')
		datas->minus_f = 1;
	else if (str[*i] == '+')
		datas->plus_f = 1;
	else if (str[*i] == '#')
		datas->hash_f = 1;
	else if (str[*i] == '0')
		datas->zero_f = 1;
	else if (str[*i] == ' ')
		datas->space_f = 1;
	else if (ft_isdigit(str[*i]))
	{
		datas->field = get_numberi((const char *)&str[*i], i);
		(*i)--;
	}
	else if (str[*i] == '.')
	{
		datas->preci = get_numberi((const char *)&str[++(*i)], i);
		(*i)--;
		(datas->preci < 0) ? (datas->preci = -1) : (datas->preci);
	}
	else if (is_mod(str[*i]))
		get_mod(datas, &str[*i], i);
	else if (conversion_char(str[*i]))
		datas->conversion = str[*i];
}

void	parse(char *str, t_print *datas)
{
	int	i;

	i = 0;
	while (str[i])
	{
		fill_data(str, &i, datas);
		i++;
	}
	free(str);
}
