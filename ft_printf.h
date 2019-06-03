/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceciora <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 15:03:26 by aceciora          #+#    #+#             */
/*   Updated: 2019/05/23 14:53:58 by aceciora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

typedef struct	s_print
{
	int			minus_f;
	int			plus_f;
	int			hash_f;
	int			zero_f;
	int			space_f;
	int			min_field;
	int			precision;
	char		*modifier;
	char		conversion;
}				t_print;
