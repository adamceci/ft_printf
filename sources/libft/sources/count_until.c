/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_until.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceciora <aceciora@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 13:24:05 by aceciora          #+#    #+#             */
/*   Updated: 2019/06/10 17:05:41 by aceciora         ###   ########.fr       */
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
		return (i);
	}
	return (0);
}
