/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceciora <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 09:54:14 by aceciora          #+#    #+#             */
/*   Updated: 2019/06/15 09:54:17 by aceciora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	change_base(uintmax_t n, int base, char *str, int i)
{
	int	rest;

	while (n > 0)
	{
		rest = n % base;
		if (rest >= 0 && rest <= 9)
			str[i - 1] = rest + '0';
		else
			str[i - 1] = rest - 10 + 'A';
		n /= base;
		i--;
	}
}

char	*ft_itoa_base(int n, int base)
{
	char	*str;
	int		i;
	int		sign;
	int		num;

	sign = 0;
	i = 0;
	if (base == 10 && n < 0)
	{
		sign = 1;
		n *= -1;
		i++;
	}
	num = n;
	while (num > 0)
	{
		i++;
		num /= base;
	}
	str = (char*)malloc(sizeof(*str) * i + 1);
	str[i] = '\0';
	change_base(n, base, str, i);
	if (sign)
		str[0] = '-';
	return (str);
}
