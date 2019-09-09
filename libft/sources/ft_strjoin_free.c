/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceciora <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 10:45:04 by aceciora          #+#    #+#             */
/*   Updated: 2019/06/18 16:37:20 by aceciora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin_free(char const *s1, char const *s2,
								int free1, int free2)
{
	char	*str;

	if (s1 && s2)
	{
		if (!(str = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		{
			(free1) ? free((void *)s1) : (0);
			(free2) ? free((void *)s2) : (0);
			return (NULL);
		}
		ft_strcpy(str, s1);
		ft_strcat(str, s2);
		(free1) ? free((void *)s1) : (0);
		(free2) ? free((void *)s2) : (0);
		return (str);
	}
	else if (s2)
	{
		if (!(str = ft_strnew(ft_strlen(s2))))
		{
			(free1) ? free((void *)s1) : (0);
			(free2) ? free((void *)s2) : (0);
			return (NULL);
		}
		ft_strcpy(str, s2);
		(free1) ? free((void *)s1) : (0);
		(free2) ? free((void *)s2) : (0);
		return (str);
	}
	return (NULL);
}
