/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceciora <aceciora@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 15:03:26 by aceciora          #+#    #+#             */
/*   Updated: 2019/06/19 17:52:56 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H

#include "libft.h"
#include <stdarg.h>
#include <inttypes.h>

#include <stdio.h> // a enlever !

typedef struct	s_strings
{
	char		*s1;
	char		*s2;
}				t_strings;


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
	int			neg;
}				t_print;

<<<<<<< HEAD
void			init_struct(t_print *datas);
=======
void			init_vars(t_strings *solve_strs, t_print *datas);
void			init_struct(t_print *datas);
void			init_f_ptr(char *(*f_ptr[256])(t_print *datas, va_list args));
intmax_t		modifiers_d_i(t_print *datas, va_list args);
uintmax_t		modifiers_o_u_x(t_print *datas, va_list args);

#endif
>>>>>>> modifiers
