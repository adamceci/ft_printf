/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_numberi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceciora <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 13:21:53 by aceciora          #+#    #+#             */
/*   Updated: 2019/06/03 13:26:41 by aceciora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_numberi(const char *str, int *i)
{
	int	value;
	int	cpt;

	cpt = 0;
	while (ft_isdigit(str[cpt]))
		cpt++;
	*i += cpt;
	value = ft_atoi(str);
	return (value);
}
