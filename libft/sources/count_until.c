/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_until.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceciora <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 13:24:05 by aceciora          #+#    #+#             */
/*   Updated: 2019/05/17 13:28:42 by aceciora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	count_until(const char *string, char c)
{
	int	i;

	if (string)
	{
		i = 0;
		while (string[i] && string[i] != c)
			i++;
		if (string[i] == c)
			return (i);
	}
	return (0);
}
