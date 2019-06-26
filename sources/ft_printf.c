/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceciora <aceciora@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 17:19:09 by aceciora          #+#    #+#             */
/*   Updated: 2019/06/24 18:57:42 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "ft_printf.h"

// PROTEGER TOUS LES MALLOCS (STRSUB STRDUP STRNEW ITOA/LLTOA/...)
// NORME ITOA
// BONUS : %ld --> type long
// Gerer le cas "%03d", -5 --> print 0-5 plutot que -05
// ADD HEADER DANS LES FICHIERS

void print_data(t_print datas)
{
	printf("- = %d\n+ = %d\n# = %d\n0 = %d\n' ' = %d\nfield = %d\npreci = %d\nconv = %c\n",
		   datas.minus_f, datas.plus_f, datas.hash_f, datas.zero_f, datas.space_f,
		   datas.field, datas.preci, datas.conversion);
	printf("modifier = %s\n", datas.modifier);
	printf("\n");
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

void	get_mod(t_print *datas, char *str, int *i)
{
	if (str[*i + 1] == str[*i])
	{
		datas->modifier = ft_strnew(2);
		datas->modifier[0] = str[*i];
		datas->modifier[1] = str[*i + 1];
		(*i)++;
	}
	else
	{
		datas->modifier = ft_strnew(1);
		datas->modifier[0] = str[*i];
	}
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
		datas->field = get_numberi((const char *)&str[*i], i);
		(*i)--;
	}
	else if (str[*i] == '.')
	{
		(*i)++;
		datas->preci = get_numberi((const char*)&str[*i], i);
		(*i)--;
		(datas->preci < 0) ? (datas->preci = -1) : (datas->preci);
	}
	else if (is_mod(str[*i]))
		get_mod(datas, &str[*i], i);
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
	free(str);
}

int		get_tot_len(t_print *datas, char *str)
{
	int	tot_len;

	tot_len = ft_strlen(str) + datas->neg;
	if (tot_len < datas->field)
		tot_len = datas->field;
	if (tot_len < datas->preci)
	{
		tot_len = datas->preci;
		if (!datas->neg && datas->plus_f)
				tot_len++;
	}
	if (datas->conversion != 'f' && datas->space_f)
		tot_len++;
	if (datas->conversion == 'f' && !datas->neg && datas->field < datas->preci)
	{
		if (datas->plus_f)
			tot_len++;
		if (datas->space_f)
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

void	put_minus(char **f_str, int neg)
{
	if (neg)
	{
		**f_str = '-';
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
	if (datas->zero_f && datas->field > len_str + datas->neg && datas->preci == -1)
		nb_zeros = datas->field - len_str - datas->neg;
	nb_spaces = (len_f_str - nb_zeros - len_str - datas->plus_f - datas->neg);
	if (datas->minus_f)
	{
		put_plus(&f_str, datas->plus_f);
		put_minus(&f_str, datas->neg);
		put_zeros(&f_str, nb_zeros);
		if (datas->space_f)
		{
			put_spaces(&f_str, nb_spaces);
			nb_spaces--;
		}
		put_value(&f_str, str, len_str);
		put_spaces(&f_str, nb_spaces);
	}
	else
	{
		put_spaces(&f_str, nb_spaces);
		put_plus(&f_str, datas->plus_f);
		put_minus(&f_str, datas->neg);
		put_zeros(&f_str, nb_zeros);
		put_value(&f_str, str, len_str);
	}
}

void	fill_f(t_print *datas, char *f_str, char *str, int len_f_str)
{
	int	nb_spaces;
	int len_str;

	len_str = ft_strlen(str);
	nb_spaces = len_f_str - len_str - datas->plus_f - datas->neg;
	if (datas->minus_f)
	{
		put_plus(&f_str, datas->plus_f);
		put_minus(&f_str, datas->neg);
		if (datas->space_f)
		{
			put_spaces(&f_str, nb_spaces);
			nb_spaces--;
		}
		put_value(&f_str, str, len_str);
		put_spaces(&f_str, nb_spaces);
	}
	else
	{
		put_plus(&f_str, datas->plus_f);
		if (!datas->zero_f)
			put_spaces(&f_str, nb_spaces);
		put_minus(&f_str, datas->neg);
		if (datas->zero_f)
			put_zeros(&f_str, nb_spaces);
		put_value(&f_str, str, len_str);
	}
}

char	*conv_X(t_print *datas, va_list args)
{
	char		*str;
	char		*f_str;
	int			len_f_str;
	uintmax_t	value;

	flag_prio_x(datas);
	value = modifiers_o_u_x(datas, args);
	if (!(str = ft_uimttoa_base(value, 16)))
		return (NULL);
	len_f_str = get_tot_len(datas, str);
	if (!(f_str = ft_strnew(len_f_str)))
		return (NULL);
	fill(datas, f_str, str, len_f_str);
	free(str);
	return (f_str);
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

char	*conv_d(t_print *datas, va_list args)
{
	char			*str;
	char			*f_str;
	int				len_f_str;
	intmax_t		value;

	if ((value = modifiers_d_i(datas, args)) < 0)
	{
		value *= -1;
		datas->neg = 1;
	}
	if (!(str = ft_imttoa(value)))
		return (NULL);
	len_f_str = get_tot_len(datas, str);
	if (!(f_str = ft_strnew(len_f_str)))
		return (NULL);
	fill(datas, f_str, str, len_f_str);
	free(str);
	return (f_str);
}

char	*ft_ftoa(long double value, int preci)
{
	intmax_t	n;
	char		*str;
	char		*final_str;

	if (preci == 0)
	{
		final_str = ft_imttoa(ft_round(value));
		return (final_str);
	}
	n = (intmax_t)value;
	value -= n;
	str = ft_strjoin_free(ft_imttoa(n), ".", 1, 0);
	while(preci > 0)
	{
		value *= 10;
		if (value < 1.0 && preci > 1)
			str = ft_strjoin_free(str, "0", 1, 0);	
		preci--;
	}
	n = ft_round(value);
	final_str = ft_strjoin_free(str, ft_imttoa(n), 1, 1);
	return (final_str);
}

char	*conv_f(t_print *datas, va_list args)
{
	char			*str;
	char			*f_str;
	int 			len_f_str;
	long double		value;

	if ((value = (long double)va_arg(args, double)) < 0)
	{
		value *= -1;
		datas->neg = 1;
	}
	if(!(str = ft_ftoa(value, datas->preci)))
		return(NULL);
	len_f_str = get_tot_len(datas, str);
	if (datas->field != -1 && datas->preci > datas->field)
		len_f_str += (ft_strlen(ft_itoa((int)value)) + 1);
	// printf("len_f_str = %d\n", len_f_str);
	if (!(f_str = ft_strnew(len_f_str)))
		return (NULL);
	fill_f(datas, f_str, str, len_f_str);
	free(str);
	return (f_str);
}

char	*conv_i(t_print *datas, va_list args)
{
	return (conv_d(datas, args));
}

char	*conv_o(t_print *datas, va_list args)
{
	char			*str;
	char			*f_str;
	int				len_f_str;
	uintmax_t		value;

	flag_prio_o(datas);
	value = modifiers_o_u_x(datas, args);
	if (!(str = ft_uimttoa_base(value, 8)))
		return (NULL);
	len_f_str = get_tot_len(datas, str);
	if (!(f_str = ft_strnew(len_f_str)))
		return (NULL);
	fill(datas, f_str, str, len_f_str);
	free(str);
	return (f_str);
}

char	*conv_p(t_print *datas, va_list args)
{
	char		*str;
	char		*str_with_prefix;
	char		*f_str;
	int			len_f_str;
	uintmax_t	value;

	value = (uintmax_t)va_arg(args, void*);
	if(!(str = ft_uimttoa_base(value, 16)))
		return (NULL);
	str_with_prefix = ft_strjoin_free("0x", str, 0, 1);
	str_with_prefix = ft_strlower(str_with_prefix);
	len_f_str = get_tot_len(datas, str_with_prefix);
	if (!(f_str = ft_strnew(len_f_str)))
		return (NULL);
	fill(datas, f_str, str_with_prefix, len_f_str);
	free(str_with_prefix);
	return (f_str);
}

void	rewrite_str(t_print *datas, char *str)
{
	int	i;

	if (datas->preci >= (int)ft_strlen(str))
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
	fill(datas, f_str, str_copy, len_f_str);
	free(str_copy);
	return (f_str);
}

char	*conv_u(t_print *datas, va_list args)
{
	char			*str;
	char			*f_str;
	int				len_f_str;
	uintmax_t		value;

	value = modifiers_o_u_x(datas, args);
	if (!(str = ft_uimttoa_base(value, 10)))
		return (NULL);
	len_f_str = get_tot_len(datas, str);
	if (!(f_str = ft_strnew(len_f_str)))
		return (NULL);
	fill(datas, f_str, str, len_f_str);
	free(str);
	return (f_str);
}

char	*conv_x(t_print *datas, va_list args)
{
	char	*f_str;
	char	*s;
	
	if (!(f_str = conv_X(datas, args)))
		return (NULL);
	s = ft_strlower(f_str);
	free(f_str);
	return (s);
}

char	*translate(t_print *datas, va_list args)
{
	char	*str;

	str = datas->f_ptr[(int)datas->conversion](datas, args);
	return (str);
}

int ft_printf(const char *format, ...)
{
	t_print		datas;
	va_list 	args;
	t_strings	solve_strs;
	int     	i;

	if (!format)
		return (0);
	va_start(args, format);
	init_vars(&solve_strs, &datas);
	i = 0;
	while (*format)
	{
		i = count_until(format, '%');
		if (!(solve_strs.s1 = ft_strjoin_free(solve_strs.s1, ft_strsub(format, 0, i), 1, 1)))
			return (-1);
		format += i;
		if (*format == '%')
		{
			format++;
			if (*format == '%')
			{
				if (!(solve_strs.s1 = ft_strjoin_free(solve_strs.s1, "%", 1, 0)))
					return (-1);
				format++;
			}
			else
			{
				init_struct(&datas);
				if (!(solve_strs.s2 = conv_infos((char**)&format)))
				{
					free(solve_strs.s1);
					return (-1);
				}
				parse(solve_strs.s2, &datas);
				// print_data(datas);
				flags_priorities(&datas);
				solve_strs.s2 = translate(&datas, args);
				if (!(solve_strs.s1 = ft_strjoin_free(solve_strs.s1, solve_strs.s2, 1, 1)))
					return (-1);
			}
		}
	}
	va_end(args);
	ft_putstr((const char*)solve_strs.s1);
	return (ft_strlen(solve_strs.s1));
}