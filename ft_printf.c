/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceciora <aceciora@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 17:19:09 by aceciora          #+#    #+#             */
/*   Updated: 2019/06/10 17:09:04 by aceciora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "ft_printf.h"

// PROTEGER TOUS LES MALLOCS (STRSUB STRDUP STRNEW ITOA/LLTOA/...)
// NORME ITOA
// BONUS : %ld --> type long
// Gerer le cas "%03d", -5 --> print 0-5 plutot que -05
// ADD HEADER DANS LES FICHIERS

int	conversion_char(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'o' ||
			c == 'u' || c == 'x' || c == 'X')
		return (1);
	return (0);
}

char	*conv_infos(char **str)
{
	int		i;
	char	*s;

	i = 0;
	while (!conversion_char((*str)[i]))
		i++;
	s = ft_strsub(*str, 0, i + 1);
	*str += (i + 1);
	return (s);
}

void fill_data(char *str, int *i, t_print *datas)
{
	if (str[*i] == '-')
		datas->minus_f = 1;
	else if (str[*i] == '+')
		datas->plus_f = 1;
	else if (str[*i] == '#')
		datas->hash_f = 1;
	else if (str[*i] == '0')
		datas->zero_f = 1;
	else if (str[*i] == ' ')
		datas->space_f = 1;
	else if (ft_isdigit(str[*i]))
	{
		datas->field = get_numberi((const char*)&str[*i], i);
		(*i)--;
	}
	else if (str[*i] == '.')
	{
		(*i)++;
		datas->preci = get_numberi((const char*)&str[*i], i);
		(*i)--;
		(datas->preci < 0) ? (datas->preci = -1) : (datas->preci);
	}
	else if (conversion_char(str[*i]))
		datas->conversion = str[*i];
	// else
	// 	gerer le cas de %10]5d par exemple ! --> remove everything between
	//	'%' and the first invalid char.
}

void	parse(char *str, t_print *datas)
{
	int	i;

	i = 0;
	while (str[i])
	{
		fill_data(str, &i, datas);
		i++;
	}
}

int		get_tot_len(t_print *datas, char *str)
{
	int	str_len;
	int	tot_len;
	int	plus;

	str_len = ft_strlen(str);
	tot_len = str_len;
	if (str_len < datas->field)
		tot_len = datas->field;
	if (tot_len < datas->preci)
	{
		tot_len = datas->preci;
		if (datas->plus_f)
			tot_len++;
	}
	return (tot_len);
}

void	put_spaces(char **f_str, int nb_spaces)
{
	int	i;

	i = 0;
	while (i < nb_spaces)
	{
		**(f_str) = ' ';
		(*f_str)++;
		i++;
	}
}

void 	put_plus(char **f_str, int plus)
{
	if (plus)
	{
		**f_str = '+';
		(*f_str)++;
	}
}

void 	put_zeros(char **f_str, int nb_zeros)
{
	int	i;

	i = 0;
	while (i < nb_zeros)
	{
		**f_str = '0';
		(*f_str)++;
		i++;
	}
}

void 	put_value(char **f_str, char *str, int len_str)
{
	int	i;

	i = 0;
	while (i < len_str)
	{
		**f_str = str[i];
		(*f_str)++;
		i++;
	}
}

void	fill(t_print *datas, char *f_str, char *str, int len_f_str)
{
	int	nb_zeros;
	int	nb_spaces;
	int	len_str;

	len_str = ft_strlen(str);
	nb_zeros = (datas->preci > len_str) ? (datas->preci - len_str) : (0);
	if (datas->zero_f && datas->field != -1 && datas->preci == -1)
		nb_zeros = datas->field - len_str;
	nb_spaces = (len_f_str - nb_zeros - len_str - datas->plus_f);
	if (datas->minus_f)
	{
		put_plus(&f_str, datas->plus_f);
		put_zeros(&f_str, nb_zeros);
		put_value(&f_str, str, len_str);
		put_spaces(&f_str, nb_spaces);
	}
	else
	{
		put_spaces(&f_str, nb_spaces);
		put_plus(&f_str, datas->plus_f);
		put_zeros(&f_str, nb_zeros);
		put_value(&f_str, str, len_str);
	}
}

void	flag_prio_x(t_print *datas)
{
	if (datas->plus_f)
		datas->plus_f = 0;
	if (datas->space_f)
		datas->space_f = 0;
}

char	*conv_X(t_print *datas, va_list args)
{
	char *str;
	char *f_str;
	int len_f_str;
	unsigned int value;

	flag_prio_x(datas);
	value = va_arg(args, unsigned int);
	if (!(str = ft_lltoa_base(value, 16)))
		return (NULL);
	len_f_str = get_tot_len(datas, str);
	if (!(f_str = ft_strnew(len_f_str)))
		return (NULL);
	// if (datas->field <= ft_strlen(str) && datas->zero_f)
	// 	datas->zero_f = 0;
	fill(datas, f_str, str, len_f_str);
	free(str);
	return (f_str);
}

void	flag_prio_c(t_print *datas)
{
	if (datas->preci != -1)
		datas->preci = -1;
}

char	*conv_c(t_print *datas, va_list args)
{
	char	str;
	char	*str_copy;
	char 	*f_str;
	int		len_f_str;

	flag_prio_c(datas);
	str = va_arg(args, int);
	if (!(str_copy = ft_strnew(1)))
		return (NULL);
	ft_strncpy(str_copy, &str, 1);
	len_f_str = get_tot_len(datas, str_copy);
	if (!(f_str = ft_strnew(len_f_str)))
		return (NULL);
	fill(datas, f_str, str_copy, len_f_str);
	free(str_copy);
	return (f_str);
}

int		deal_neg_value(t_print *datas, int value, char *str)
{
	if (*str == '-' && datas->zero_f && datas->field > ft_strlen(str))
		return (1);
	return (0);
}

char	*conv_d(t_print *datas, va_list args)
{
	char			*str;
	char			*f_str;
	int				len_f_str;
	int				value;
	int				neg;

	neg = 0;
	value = va_arg(args, int);
	if (!(str = ft_itoa(value)))
		return (NULL);
	neg = deal_neg_value(datas, value, str);	// a faire !!
	len_f_str = get_tot_len(datas, str);
	if (!(f_str = ft_strnew(len_f_str)))
		return (NULL);
	if (datas->field <= ft_strlen(str) && datas->zero_f)
		datas->zero_f = 0;
	fill(datas, f_str, str, len_f_str);
	free(str);
	return (f_str);
}

char	*conv_f(t_print *datas, va_list args)
{
	return (NULL);
}

char	*conv_i(t_print *datas, va_list args)
{
	return (conv_d(datas, args));
}

void	flag_prio_o(t_print *datas)
{
	if (datas->space_f)
		datas->space_f = 0;
	if (datas->plus_f)
		datas->plus_f = 0;
}

char	*conv_o(t_print *datas, va_list args)
{
	char			*str;
	char			*f_str;
	int				len_f_str;
	unsigned int	value;

	flag_prio_o(datas);
	value = va_arg(args, unsigned int);
	if (!(str = ft_lltoa_base(value, 8)))
		return (NULL);
	len_f_str = get_tot_len(datas, str);
	if (!(f_str = ft_strnew(len_f_str)))
		return (NULL);
	if (datas->field <= ft_strlen(str) && datas->zero_f)
		datas->zero_f = 0;
	fill(datas, f_str, str, len_f_str);
	free(str);
	return (f_str);
}

char	*conv_p(t_print *datas, va_list args)
{
	return (NULL);
}

void	rewrite_str(t_print *datas, char *str)
{
	int	i;

	if (datas->preci >= ft_strlen(str))
		datas->preci = -1;
	else
	{
		i = 0;
		while (datas->preci > 0)
		{
			i++;
			datas->preci--;
		}
		str[i] = '\0';
	}
}

char	*conv_s(t_print *datas, va_list args)
{
	char	*str;
	char	*str_copy;
	char	*f_str;
	int		len_f_str;

	str = va_arg(args, char*);
	if (!(str_copy = ft_strdup((const char*)str)))
		return (NULL);
	rewrite_str(datas, str_copy);
	len_f_str = get_tot_len(datas, str_copy);
	if (!(f_str = ft_strnew(len_f_str)))
		return (NULL);
	if (datas->field <= ft_strlen(str) && datas->zero_f)
		datas->zero_f = 0;
	fill(datas, f_str, str_copy, len_f_str);
	free(str_copy);
	return (f_str);
}

char	*conv_u(t_print *datas, va_list args)
{
	char			*str;
	char			*f_str;
	int				len_f_str;
	unsigned int	value;

	value = va_arg(args, unsigned int);
	if (!(str = ft_lltoa(value)))
		return (NULL);
	len_f_str = get_tot_len(datas, str);
	if (!(f_str = ft_strnew(len_f_str)))
		return (NULL);
	// if (datas->field <= ft_strlen(str) && datas->zero_f)
	// 	datas->zero_f = 0;
	fill(datas, f_str, str, len_f_str);
	free(str);
	return (f_str);
}

void	lowercase(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
}

char	*conv_x(t_print *datas, va_list args)
{
	char *f_str;
	
	if (!(f_str = conv_X(datas, args)))
		return (NULL);
	lowercase(f_str);
	return (f_str);
}

void	init_f_ptr(char *(*f_ptr[256])(t_print *datas, va_list args))
{
	ft_bzero(f_ptr, 256);
	f_ptr[88] = &(conv_X);
	f_ptr[99] = &(conv_c);
	f_ptr[100] = &(conv_d);
	f_ptr[102] = &(conv_f);
	f_ptr[105] = &(conv_i);
	f_ptr[111] = &(conv_o);
	f_ptr[112] = &(conv_p);
	f_ptr[115] = &(conv_s);
	f_ptr[117] = &(conv_u);
	f_ptr[120] = &(conv_x);
}

char	*translate(t_print *datas, va_list args)
{
	char	*str;

	str = datas->f_ptr[datas->conversion](datas, args);
	return (str);
}

int	numeric_conversion(char c)
{
	if (c == 'd' || c == 'i' || c == 'o' || c == 'u' || c == 'x' || c == 'X')
		return (1);
	return (0);
}

void flag_priorities(t_print *datas)
{
	if (datas->conversion == 's' || datas->conversion == 'c' ||
			datas->conversion == 'p')
	{
		datas->plus_f = 0;
		datas->hash_f = 0;
		datas->zero_f = 0;
		datas->space_f = 0;
		if (datas->conversion == 'c' || datas->conversion == 'p')
			datas->preci = -1;
	}
	if (numeric_conversion(datas->conversion))
	{
		if (datas->zero_f && datas->preci != -1)
			if (datas->preci != -1 || datas->minus_f)
				datas->zero_f = 0;
		if (datas->plus_f && datas->space_f)
			datas->space_f = 0;
		if (datas->field <= datas->preci)
			datas->field = -1;
	}
}

int ft_printf(const char *format, ...)
{
	t_print	datas;
	va_list args;
	char    *s1;
	char    *s2;
	int     i;

	if (!format)
		return (0);
	s1 = ft_strnew(0);
	s2 = NULL;
	va_start(args, format);
	init_f_ptr(datas.f_ptr);
	i = 0;
	while (*format)
	{
		i = count_until(format, '%');
		s1 = ft_strjoin_free(s1, ft_strsub(format, 0, i), 1, 1);
		format += i;
		if (*format == '%')
		{
			format++;
			init_struct(&datas);
			s2 = conv_infos((char**)&format);
			parse(s2, &datas);
			free(s2);
			flag_priorities(&datas);
			s2 = translate(&datas, args);
			s1 = ft_strjoin_free(s1, s2, 1, 1);
		}
	}
	va_end(args);
	ft_putstr((const char*)s1);
	return (ft_strlen(s1));
}

int main()
{
	ft_printf("%010d", -5);
	// printf("%01uyes\n", 429495);
	// ft_printf("%01uyes\n", 429495);
	//
	// ft_printf("|%-+.20d|\n\n", 12);
	// ft_printf("4567 |%-10]5d| plip\n", 12);
	// ft_printf("4567 |%10]5d| plip\n", 12);
	// ft_printf("|%10.5d|\n", -12);
	// ft_printf("|%010d|\n", -12);
	// ft_printf("|%-10.5d|\n", -12);
	// ft_printf("|%-010.5d|\n", -12);
	//
	// printf("|%-+.20d|\n\n", 12);
	// printf("4567 |%-10]5d| plip\n", 12);
	// printf("4567 |%10]5d| plip\n", 12);

	// printf("|%10.5d|\n", -12);
	// ft_printf("|%10.5d|\n", -12);
	// printf("\n");
	// printf("|%010d|\n", -12);
	// ft_printf("|%010d|\n", -12);
	// printf("\n");
	// printf("|%-10.5d|\n", -12);
	// ft_printf("|%-10.5d|\n", -12);
	// printf("\n");
	// printf("|%-010.5d|\n", -12);
	// ft_printf("|%-010.5d|\n", -12);
	return (0);
}