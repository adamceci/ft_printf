/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceciora <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 16:38:56 by aceciora          #+#    #+#             */
/*   Updated: 2019/06/21 16:37:40 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_imttoa(intmax_t n)
{
	char	*str;
	int		nb_chars;
	int		i;
	int		sign;

	nb_chars = ft_count_chars(n);
	if (!(str = ft_strnew(nb_chars)))
		return (NULL);
	sign = (n < 0) ? (1) : (0);
	i = nb_chars - 1;
	if (n < 0)
		n *= -1;
	while (i >= 0)
	{
		str[i] = ft_fill_char(str, &n);
		i--;
	}
	if (sign)
		str[0] = '-';
	return (str);
}
