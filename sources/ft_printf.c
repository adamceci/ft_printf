/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceciora <aceciora@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 17:19:09 by aceciora          #+#    #+#             */
/*   Updated: 2019/06/21 17:05:53 by apalaz           ###   ########.fr       */
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

int	is_mod(char c)
{
	if (c == 'l' || c == 'h')
		return (1);
	return (0);
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
	int len_str;

	len_str = ft_strlen(str);
	put_spaces(&f_str, datas->space_f);
	printf("1 = %s\n", f_str);
	put_plus(&f_str, datas->plus_f);
	printf("2 = %s\n", f_str);
	put_value(&f_str, str, len_str);
	printf("3 = %s\n", f_str);
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

	printf("preci = %d\n", preci);
	n = (intmax_t)value;
	value -= n;
	str = ft_strjoin_free(ft_imttoa(n), ".", 1, 0);
	// preci 0 --> %.f
	if (preci == -1)
		preci = 6;
	while(preci > 0)
	{
		value *= 10;
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
	int len_f_str;
	long double		value;

	value = (long double)va_arg(args, double);
	if(!(str = ft_ftoa(value, datas->preci)))
		return(NULL);
	datas->preci = -1;
	len_f_str = get_tot_len(datas, str);
	if (!(f_str = ft_strnew(len_f_str)))
		return (NULL);
	printf("f_str 1 = %s\n", f_str);
	fill_f(datas, f_str, str, len_f_str);
	printf("f_str 2 = %s\n", f_str);
	free(str);
	return (f_str);
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

void	init_f_ptr(char *(*f_ptr[256])(t_print *datas, va_list args))
{
	ft_bzero(f_ptr, 256);
	f_ptr[88] = &(conv_X);
	f_ptr[99] = &(conv_c);
	f_ptr[100] = &(conv_d);
	f_ptr[48] = &(conv_f);
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

	str = datas->f_ptr[(int)datas->conversion](datas, args);
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
		if (datas->zero_f)
			if (datas->preci != -1 || datas->minus_f)
				datas->zero_f = 0;
		if (datas->plus_f && datas->space_f)
			datas->space_f = 0;
		if (datas->field <= datas->preci)
			datas->field = -1;
	}
	if (datas->conversion == 'f')
	{
		datas->field = -1;
		datas->minus_f = 0;
	}
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
				flag_priorities(&datas);
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

int main()
{
	// printf("%lld\n", -10000000000000000000);
	// ft_printf("%lld\n", -10000000000000000000);
	// printf("%d\n", 2000000);
	// ft_printf("%d\n", 2000000);

	 printf("printf = %.2f\n", 1234.5690);
	 ft_printf("ft_printf = %.2f\n", 1234.5690);

	//  printf("printf = %.0f\n", 0.5690);
	//  ft_printf("ft_printf = %.0f\n", 0.5690);

	//  printf("printf = % -f\n", 1234.5690);
	//  ft_printf("ft_printf = % -f\n", 1234.5690);

	//  printf("printf = %20.2f\n", 1234.5690);
	//  ft_printf("ft_printf = %20.2f\n", 1234.5690);

	// printf("x = %x\n", "salut");
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

	// TESTS OK :
	//
	// printf("%u\n", -1000000000000);
	// ft_printf("%u\n", -1000000000000);
	// printf('\n');
	// printf("%01d\n", -100);
	// ft_printf("%01d\n", -100);
	// printf("\n");
	// printf("%010o\n", -100);
	// ft_printf("%010o\n", -100);
	// printf("\n");
	// printf("%010x\n", -100);
	// ft_printf("%010x\n", -100);
	// printf("\n");
	// printf("%010u\n", -100);
	// ft_printf("%010u\n", -100);
	// printf("\n");
	// printf("%%%4d\n", 13);
	// ft_printf("%%%4d\n", 13);
	// printf('\n');
	// printf("%x\n", 548045);
	// ft_printf("%x\n", 548045);
	// printf("\n");
	// printf("%X\n", -548045);
	// ft_printf("%X\n", -548045);
	// printf("\n");
	// printf("%01uyes\n", 429495);
	// ft_printf("%01uyes\n", 429495);
	// printf("\n");
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
