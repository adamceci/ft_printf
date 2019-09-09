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

char	*conv_infos(char **str)
{
	int		i;
	char	*s;

	i = 0;
	while ((*str)[i] && !conversion_char((*str)[i]))
		i++;
	if (!(*str)[i])
	{
		s = ft_strsub(*str, 0, i);
		*str += i;
	}
	else
	{
		s = ft_strsub(*str, 0, i + 1);
		*str += (i + 1);
	}
	return (s);
}

void	get_mod(t_print *datas, char *str, int *i)
{
	if (str[*i + 1] == str[*i])
	{
		datas->modifier = ft_strnew(2);
		datas->modifier[0] = str[*i];
		datas->modifier[1] = str[*i];
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
		get_mod(datas, str, i);
	else if (conversion_char(str[*i]))
		datas->conversion = str[*i];
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

int len_specific_case(t_print *datas, char *str, int tot_len)
{
	if (datas->conversion == 'X' || datas->conversion == 'o' || datas->conversion == 'd' ||
		datas->conversion == 'p' || datas->conversion == 'u')
	{
		if (!ft_strcmp(str, "0"))
			datas->is_nil = 1;
		if (!datas->is_nil)
		{
			if (datas->conversion == 'X')
			{
				if (datas->hash_f)
				{
					if (tot_len == datas->field)
					{
						if (tot_len < (int)ft_strlen(str) + 2)
							tot_len += ft_strlen(str) + 2 - datas->field;
					}
					else
						tot_len += 2;
				}
			}
			else if (datas->conversion == 'o')
			{
				if (datas->hash_f && (tot_len < (int)ft_strlen(str)))
					tot_len++;
			}
		}
		else
		{
			if (!datas->preci && datas->field == -1)
				tot_len--;
			if (datas->conversion == 'o' && datas->hash_f && !datas->preci)
				tot_len++;
		}
	}
	return (tot_len);
}

int		get_tot_len(t_print *datas, char *str)
{
	int	tot_len;

	(str) ? (tot_len = ft_strlen(str) + datas->neg) : (tot_len = 0);
	// printf("str = %s\n", str);
	if (tot_len < datas->field)
		tot_len = datas->field;
	if (tot_len < datas->preci)
	{
		tot_len = datas->preci;
		if ((!datas->neg && datas->plus_f) || datas->neg)
			tot_len++;
	}
	if (datas->conversion == 'd' && datas->plus_f && datas->field < tot_len && datas->preci == -1)
		tot_len++;
	if (datas->conversion != 'f' && datas->conversion != '%' && datas->conversion != 'd' && datas->space_f)
		tot_len++;
	if (datas->conversion == 'f' && !datas->neg && datas->field < datas->preci)
	{
		if (datas->plus_f)
			tot_len++;
		if (datas->space_f)
			tot_len++;
	}
	tot_len = len_specific_case(datas, str, tot_len);
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

void	put_hash(char **f_str, t_print *datas, char *str)
{
	if (datas->hash_f)
	{
		if (datas->conversion == 'X' && !datas->is_nil)
		{
			ft_strcpy(*f_str, "0X");
			(*f_str) += 2;
		}
		else if (datas->conversion == 'o' && ((!datas->is_nil && datas->preci < (int)ft_strlen(str)) || (datas->is_nil && !datas->preci)))
		{
			ft_strcpy(*f_str, "0");
			(*f_str)++;
		}
	}
}

void	put_prefix(char **f_str)
{
	**f_str = '0';
	(*f_str)++;
	**f_str = 'x';
	(*f_str)++;
}

void 	put_value(char **f_str, char *str, int len_str, t_print *datas)
{
	int	i;

	if (datas->conversion == '%')
	{
		**f_str = '%';
		(*f_str)++;
	}
	else if (!(datas->is_nil && !datas->preci))
	{
		i = 0;
		while (i < len_str)
		{
			**f_str = str[i];
			(*f_str)++;
			i++;
		}
	}
}

void	fill(t_print *datas, char *f_str, char *str, int len_f_str)
{
	int	nb_zeros;
	int	nb_spaces;
	int	len_str;

	(str) ? (len_str = ft_strlen(str)) : (len_str = 0);
	if (datas->conversion == 'c' && datas->is_nil && datas->field > 0)
		len_str = 1;
	if (datas->is_nil && !datas->preci)
		len_str = 0;
	nb_zeros = (datas->preci > len_str) ? (datas->preci - len_str) : (0);
	// printf("0 = %d\n", nb_zeros);
	if (datas->zero_f && datas->field > len_str + datas->neg && datas->preci == -1)
	{
		nb_zeros = datas->field - len_str - datas->neg - datas->plus_f - datas->space_f;
		// printf("0 = %d\n", nb_zeros);
		if (datas->conversion == 'X' && datas->hash_f)
			nb_zeros -= 2;
		if (datas->conversion == 'o' && datas->hash_f)
			nb_zeros -= 1;
	}
	nb_spaces = len_f_str - nb_zeros - len_str - datas->plus_f - datas->neg;
	if (datas->conversion == 'X' && datas->hash_f && !datas->is_nil)
		nb_spaces -= 2;
	if (datas->conversion == '%' || (datas->conversion == 'o' && datas->hash_f && !datas->is_nil) ||
		(datas->is_nil && !datas->preci && datas->field < len_str))
		nb_spaces -= 1;
	(nb_spaces < 0) ? (nb_spaces = 0) : (0);
	if (!nb_spaces && datas->space_f)
		nb_spaces++;
	// printf("0 = %d - ' ' = %d\n", nb_zeros, nb_spaces);
	// printf("len = %d\n", len_f_str);
	if (datas->minus_f)
	{
		put_plus(&f_str, datas->plus_f);
		put_minus(&f_str, datas->neg);
		if (datas->space_f)
		{
			put_spaces(&f_str, 1);
			nb_spaces--;
		}
		put_zeros(&f_str, nb_zeros);
		put_hash(&f_str, datas, str);
		put_value(&f_str, str, len_str, datas);
		put_spaces(&f_str, nb_spaces);
	}
	else
	{
		put_spaces(&f_str, nb_spaces);
		put_plus(&f_str, datas->plus_f);
		put_minus(&f_str, datas->neg);
		put_hash(&f_str, datas, str);
		put_zeros(&f_str, nb_zeros);
		put_value(&f_str, str, len_str, datas);
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
		put_value(&f_str, str, len_str, datas);
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
		put_value(&f_str, str, len_str, datas);
	}
}

void	fill_p(t_print *datas, char *f_str, char *str, int len_f_str)
{
	int	nb_zeros;
	int	nb_spaces;
	int	len_str;
	const int	prefix_size = 2;

	(str) ? (len_str = ft_strlen(str)) : (len_str = 0);
	nb_zeros = (datas->preci > len_str) ? (datas->preci - len_str) : (0);
	if (datas->zero_f && datas->field > len_str && datas->preci == -1)
		nb_zeros = datas->field - len_str - prefix_size;
	nb_spaces = (len_f_str - nb_zeros - len_str - prefix_size);
	(nb_spaces < 0) ? (nb_spaces = 0) : (0);
	if (datas->minus_f)
	{
		put_prefix(&f_str);
		put_zeros(&f_str, nb_zeros);
		put_value(&f_str, str, len_str, datas);
		put_spaces(&f_str, nb_spaces);
	}
	else
	{
		put_spaces(&f_str, nb_spaces);
		put_prefix(&f_str);
		put_zeros(&f_str, nb_zeros);
		put_value(&f_str, str, len_str, datas);
	}
}

void	flag_prio_percent(t_print *datas)
{
	datas->plus_f = 0;
	datas->hash_f = 0;
	datas->space_f = 0;
	if (datas->preci)
		datas->preci = -1;
}

char	*conv_percent(t_print *datas, va_list args)
{
	char	*str;
	char	*f_str;
	int		len_f_str;

	args = NULL;
	str = NULL;
	flag_prio_percent(datas);
	len_f_str = get_tot_len(datas, str);
	if (!len_f_str)
		len_f_str += 1;
	if (!(f_str = ft_strnew(len_f_str)))
		return (NULL);
	fill(datas, f_str, str, len_f_str);
	datas->tot_len += len_f_str;
	return (f_str);
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
	// printf("len = %d\n", len_f_str);
	if (!(f_str = ft_strnew(len_f_str)))
		return (NULL);
	fill(datas, f_str, str, len_f_str);
	free(str);
	datas->tot_len += len_f_str;
	return (f_str);
}

char	*conv_c(t_print *datas, va_list args, char **solve_str)
{
	char	c;
	char	*str_copy;
	char 	*f_str;
	int		len_f_str;

	flag_prio_c(datas);
	c = va_arg(args, int);
	if (!c)
		datas->is_nil = 1;
	if (!(str_copy = ft_strnew(1)))
		return (NULL);
	ft_strncpy(str_copy, &c, 1);
	len_f_str = get_tot_len(datas, str_copy);
	if (!(f_str = ft_strnew(len_f_str)))
		return (NULL);
	fill(datas, f_str, str_copy, len_f_str);
	free(str_copy);
	datas->tot_len += len_f_str;
	if (!c)
	{
		if (datas->field == -1)
			datas->tot_len++;
		ft_putstr((const char *)*solve_str);
		free(*solve_str);
		*solve_str = ft_strnew(0);
		ft_putstr(f_str);
		ft_putchar(c);
		return (f_str = ft_strnew(0));
	}
	return (f_str);
}

void	flag_prio_d(t_print *datas)
{
	if (datas->field > datas->len_str && !datas->zero_f && !datas->minus_f)
		datas->space_f = 0;
	if(datas->neg)
	{
		datas->space_f = 0;
		datas->plus_f = 0;
	}
}

char	*conv_d(t_print *datas, va_list args)
{
	char			*str;
	char			*f_str;
	int				len_f_str;
	intmax_t		value;

	if ((value = modifiers_d_i(datas, args)) < 0)
	{
		if (value == (intmax_t)LLLIMIT)
		{
			datas->tot_len += 20;
			return (f_str = ft_strdup("-9223372036854775808"));
		}
		value *= -1;
		datas->neg = 1;
	}
	if (!(str = ft_imttoa(value)))
		return (NULL);
	datas->len_str = ft_strlen(str);
	flag_prio_d(datas);
	len_f_str = get_tot_len(datas, str);
	if (!(f_str = ft_strnew(len_f_str)))
		return (NULL);
	fill(datas, f_str, str, len_f_str);
	free(str);
	// printf("tot_len = %d\n", len_f_str);
	datas->tot_len += len_f_str;
	return (f_str);
}

char	*ft_ftoa(long double value, int preci)
{
	intmax_t	n;
	long double	decimal;
	int			i;
	char		*str;
	char		*final_str;


	if (preci == 0)
	{
		final_str = ft_imttoa(ft_round((intmax_t)value));
		return (final_str);
	}
	str = NULL;
	decimal = (intmax_t)value * 1.0;
	// printf("decimal = %Lf\n", decimal);
	value -= decimal;
	i = preci;
	while (i > 0)
	{
		// printf("val = %Lf\n", value);
		// printf("diff = %Lf\n", 1.0 - value);
		value *= 10.0;
		// int int_value = (int)value;
		// printf("int_value = %d\n", int_value);
		// printf("val =  %Lf\n", value);
		if (value < 1.0 && i > 1)
		{
			// A REGLER : CAS 1.001000000 ?????????
			// printf("vafdsfdsl = %Lf\n", value);
			str = ft_strjoin_free(str, "0", 1, 0);
			// printf("str = %s\n", str);
		}
		i--;
	}
	n = ft_round(value);
	if ((long double)n > value && ft_imttoa(n)[0] == '1')
	{
		decimal++;
		final_str = ft_strjoin_free(ft_itoa(decimal), ".", 1, 0);
		i = preci;
		while (i > 0)
		{
			final_str = ft_strjoin_free(final_str, "0", 1, 0);
			i--;
		}
	}
	else
	{
		final_str = ft_strjoin_free(ft_itoa(decimal), ".", 1, 0);
		if (str)
		{
			final_str = ft_strjoin_free(final_str, str, 1, 1);
		}
		final_str = ft_strjoin_free(final_str, ft_imttoa(n), 1, 1);
	}
	return (final_str);
}

char	*conv_f(t_print *datas, va_list args)
{
	char			*str;
	char			*f_str;
	int 			len_f_str;
	long double		value;

	if ((value = modifiers_f(datas, args)) < 0)
	{
		value *= -1;
		datas->neg = 1;
	}
	if(!(str = ft_ftoa(value, datas->preci)))
		return(NULL);
	len_f_str = get_tot_len(datas, str);
	if (datas->field != -1 && datas->preci > datas->field)
		len_f_str += (ft_strlen(ft_itoa((int)value)) + 1);
	if (!(f_str = ft_strnew(len_f_str)))
		return (NULL);
	fill_f(datas, f_str, str, len_f_str);
	free(str);
	if (datas->preci == 0 && datas->hash_f)
		f_str = ft_strjoin_free(f_str, ".", 1, 0);
	datas->tot_len += len_f_str;
	return (f_str);
}

char	*conv_i(t_print *datas, va_list args)
{
	datas->conversion = 'd';
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
	datas->tot_len += len_f_str;
	return (f_str);
}

char	*conv_p(t_print *datas, va_list args)
{
	char		*str;
	char		*f_str;
	int			len_f_str;
	uintmax_t	value;
	const int	prefix_size = 2;

	value = (uintmax_t)va_arg(args, void *);
	if(!(str = ft_uimttoa_base(value, 16)))
		return (NULL);
	if (!value && !datas->preci)
	{
		free(str);
		datas->tot_len += 2;
		return (f_str = ft_strdup("0x"));
	}
	str = ft_strlower_free(str, 1);
	len_f_str = get_tot_len(datas, str);
	if (len_f_str > datas->field)
		len_f_str += prefix_size;
	if (!(f_str = ft_strnew(len_f_str)))
		return (NULL);
	fill_p(datas, f_str, str, len_f_str);
	free(str);
	datas->tot_len += len_f_str;
	return (f_str);
}

void	rewrite_str(t_print *datas, char *str)
{
	int	i;

	if (datas->preci >= (int)ft_strlen(str))
		datas->preci = -1;
	else if (datas->preci > -1)
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

	if (!(str = va_arg(args, char *)))
		str = ft_strdup("(null)");
	if (!(str_copy = ft_strdup((const char *)str)))
		return (NULL);
	rewrite_str(datas, str_copy);
	len_f_str = get_tot_len(datas, str_copy);
	if (!(f_str = ft_strnew(len_f_str)))
		return (NULL);
	fill(datas, f_str, str_copy, len_f_str);
	free(str_copy);
	datas->tot_len += len_f_str;
	return (f_str);
}

void	flag_prio_u(t_print *datas)
{
	if (datas->space_f)
		datas->space_f = 0;
	if (datas->plus_f)
		datas->plus_f = 0;
}

char	*conv_u(t_print *datas, va_list args)
{
	char			*str;
	char			*f_str;
	int				len_f_str;
	uintmax_t		value;

	value = modifiers_o_u_x(datas, args);
	flag_prio_u(datas);
	if (!(str = ft_uimttoa_base(value, 10)))
		return (NULL);
	len_f_str = get_tot_len(datas, str);
	if (!(f_str = ft_strnew(len_f_str)))
		return (NULL);
	fill(datas, f_str, str, len_f_str);
	free(str);
	datas->tot_len += len_f_str;
	return (f_str);
}

char	*conv_x(t_print *datas, va_list args)
{
	char	*f_str;
	char	*s;

	datas->conversion = 'X';
	if (!(f_str = conv_X(datas, args)))
		return (NULL);
	s = ft_strlower(f_str);
	free(f_str);
	return (s);
}

char	*translate(t_print *datas, va_list args, char **solve_str)
{
	char	*str;

	if (datas->conversion == 'c')
		str = conv_c(datas, args, solve_str);
	else
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
		datas.tot_len += i;
		format += i;
		if (*format == '%')
		{
			format++;
			if (*format == '%')
			{
				if (!(solve_strs.s1 = ft_strjoin_free(solve_strs.s1, "%", 1, 0)))
					return (-1);
				datas.tot_len++;
				format++;
			}
			else
			{
				init_struct(&datas);
				if (!(solve_strs.s2 = conv_infos((char **)&format)))
				{
					free(solve_strs.s1);
					return (-1);
				}
				parse(solve_strs.s2, &datas);
				if (datas.conversion == '0')
					return (0);
				flags_priorities(&datas);
				solve_strs.s2 = translate(&datas, args, &solve_strs.s1);
				if (!(solve_strs.s1 = ft_strjoin_free(solve_strs.s1, solve_strs.s2, 1, 1)))
					return (-1);
			}
		}
	}
	va_end(args);
	ft_putstr((const char*)solve_strs.s1);
	((size_t)datas.tot_len < ft_strlen(solve_strs.s1)) ? (datas.tot_len = ft_strlen(solve_strs.s1)) : (0);
	return (datas.tot_len);
}