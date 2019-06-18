/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceciora <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 16:38:56 by aceciora          #+#    #+#             */
/*   Updated: 2019/06/18 16:39:29 by aceciora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_lltoa(long long n)
{
	char	*str;
	int		nb_chars;
	int		i;

	nb_chars = ft_count_chars(n);
	if (!(str = ft_strnew(nb_chars)))
		return (NULL);
	i = nb_chars - 1;
	while (i >= 0)
	{
		str[i] = ft_fill_char(str, &n);
		i--;
	}
	return (str);
}
