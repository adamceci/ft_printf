/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceciora <aceciora@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 15:03:26 by aceciora          #+#    #+#             */
/*   Updated: 2019/06/05 18:43:27 by aceciora         ###   ########.fr       */
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
	int			field;
	int			preci;
	char		*modifier;
	char		conversion;
	char		*(*f_ptr[256])(struct s_print *datas, va_list args);
}				t_print;

void			init_struct(t_print *datas);