/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_round.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 16:32:48 by apalaz            #+#    #+#             */
/*   Updated: 2019/06/21 17:04:33 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

uintmax_t		ft_round(long double value)
{
	if ((value - (uintmax_t)value) >= 0.5)
		return ((uintmax_t)value + 1);
	else
		return((uintmax_t)value);
}
