/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceciora <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 16:38:05 by aceciora          #+#    #+#             */
/*   Updated: 2019/06/18 16:38:41 by aceciora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_uimttoa_base(uintmax_t n, int base)
{
	char		*str;
	int			i;
	uintmax_t	num;

	num = n;
	i = 0;
	while (num > 0)
	{
		i++;
		num /= base;
	}
	if (!(str = (char *)malloc(sizeof(*str) * (i + 1))))
		return (NULL);
	str[i] = '\0';
	change_base(n, base, str, i);
	return (str);
}
