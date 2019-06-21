/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceciora <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:50:26 by aceciora          #+#    #+#             */
/*   Updated: 2019/06/18 16:39:58 by aceciora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_count_chars(intmax_t n)
{
	int			nb_chars;

	nb_chars = 0;
	if (n == 0)
		return (1);
	else
	{
		if (n < 0)
		{
			nb_chars++;
			n *= -1;
		}
		while (n > 0)
		{
			n /= 10;
			nb_chars++;
		}
	}
	return (nb_chars);
}

char	ft_fill_char(char *str, intmax_t *n)
{
	if (*n >= 10)
	{
		*str = (*n % 10) + '0';
		*n /= 10;
	}
	else if (*n >= 0 && *n < 10)
		*str = *n + '0';
	return (*str);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			nb_chars;
	int			i;
	int			sign;
	intmax_t	num;

	num = (intmax_t)n;
	nb_chars = ft_count_chars(num);
	str = ft_strnew(nb_chars);
	if (!str)
		return (NULL);
	sign = (n < 0) ? (1) : (0);
	i = nb_chars - 1;
	if (num < 0)
		num *= -1;
	while (i >= 0)
	{
		str[i] = ft_fill_char(str, &num);
		i--;
	}
	if (sign)
		str[0] = '-';
	return (str);
}
