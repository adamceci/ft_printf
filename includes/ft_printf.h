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

int				ft_printf(const char *format, ...);
char			*conv_X(t_print *datas, va_list args);
char			*conv_x(t_print *datas, va_list args);
char			*conv_d(t_print *datas, va_list args);
char			*conv_i(t_print *datas, va_list args);
char			*conv_o(t_print *datas, va_list args);
char			*conv_u(t_print *datas, va_list args);
char			*conv_f(t_print *datas, va_list args);
char 			*conv_s(t_print *datas, va_list args);
char 			*conv_c(t_print *datas, va_list args);
char 			*conv_p(t_print *datas, va_list args);
void 			init_f_ptr(char *(*f_ptr[256])(t_print *datas, va_list args));
void			init_vars(t_strings *solve_strs, t_print *datas);
void			init_struct(t_print *datas);
void			init_f_ptr(char *(*f_ptr[256])(t_print *datas, va_list args));
int				conversion_char(char c);
int				numeric_conversion(char c);
int				is_mod(char c);
void			flags_priorities(t_print *datas);
void 			flag_prio_c(t_print *datas);
void 			flag_prio_x(t_print *datas);
void			flag_prio_o(t_print *datas);
void			get_mod(t_print *datas, char *str, int *i);
void			fill_data(char *str, int *i, t_print *datas);
void			parse(char *str, t_print *datas);
intmax_t		modifiers_d_i(t_print *datas, va_list args);
uintmax_t		modifiers_o_u_x(t_print *datas, va_list args);
long double		modifiers_f(t_print *datas, va_list args);

#endif