/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceciora <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 13:07:20 by aceciora          #+#    #+#             */
/*   Updated: 2019/05/14 13:20:30 by aceciora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, unsigned int start, unsigned int end)
{
	char			*copy;
	unsigned int	i;

	copy = (char*)malloc(sizeof(*copy) * (end - start) + 1);
	if (!copy)
		return (NULL);
	i = start;
	while (i < end)
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
