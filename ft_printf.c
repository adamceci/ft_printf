/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceciora <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 17:19:09 by aceciora          #+#    #+#             */
/*   Updated: 2019/05/28 17:25:57 by aceciora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <stdarg.h>
#include "libft.h"
#include "ft_printf.h"

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

/*
void	ft_d(va_list args, t_print *datas)
{
	int		val;

	val = va_arg(args, int);
	printf("val = %d\n", val);
}

void	ft_c(va_list args, t_print *datas)
{
	char	val;

	val = va_arg(args, int);
	printf("val = %c\n", val);
}
*/

// A METTRE DANS LA LIB
int	get_numberi(const char *str, int *i)
{
	int	value;
	int	cpt;

	cpt = 0;
	while (ft_isdigit(str[cpt]))
		cpt++;
	*i += cpt;
	value = ft_atoi(str);
	return (value);
}

void	parse(char *str, va_list args, t_print *datas)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '-')
			datas->minus_f = 1;
		else if (str[i] == '+')
			datas->plus_f = 1;
		else if (str[i] == '#')
			datas->hash_f = 1;
		else if (str[i] == '0')
			datas->zero_f = 1;
		else if (str[i] == ' ')
			datas->space_f = 1;
		else if (ft_isdigit(str[i]))
		{
			datas->min_field = get_numberi((const char*)&str[i], &i);
			i--;
		}
		else if (str[i] == '.')
		{
			i++;
			datas->precision = get_numberi((const char*)&str[i], &i);
			i--;
		}
		else if (conversion_char(str[i]))
			datas->conversion = str[i];
		i++;
	}
}

/*
void	translate(char *str)
{
	char	*s;
	char * (*f[255]) (va_list args, t_print data);

	// i = dernier
	s = f[t_print.coversion](args,
	if (str[i] == 'd')
		ft_d();
	else if (str[i] == 'i')
		ft_i();
	else if ()

	ft_putstr(s);
}
*/

void init_struct(t_print *datas)
{
	datas->minus_f = 0;
	datas->plus_f = 0;
	datas->hash_f = 0;
	datas->zero_f = 0;
	datas->space_f = 0;
	datas->min_field = -1;
	datas->precision = -1.0;
	datas->conversion = '0';
}

void print_data(t_print datas)
{
	printf("minus_f = %d\nplus_f = %d\nhash_f = %d\nzero_f = %d\nspace_f = %d\nmin_field = %d\nprecision = %d\nconversion = %c\n", datas.minus_f, datas.plus_f,
					datas.hash_f, datas.zero_f, datas.space_f, datas.min_field,
					datas.precision, datas.conversion);
	printf("\n");
}

int ft_printf(const char *format, ...)
{
	t_print	datas;
	va_list args;
	char    *s1;
	char    *s2;
	int     i;

	if (format == NULL)
		return (0);
	s1 = ft_strnew(0);
	s2 = NULL;
	// datas.init_str = (char*)format;
	va_start(args, format);
	i = 0;
	while (*format)
	{
			i = count_until(format, '%');
			// /!\ IF NO '%' --> COUNT_UNTIL RETURNS 0 !!)
			s1 = ft_strjoin_free(s1, ft_strsub(format, 0, i), 1, 1);
			format += i;
			if (*format++ == '%')
			{
				init_struct(&datas);
				s2 = conv_infos((char**)&format);
				parse(s2, args, &datas);
				printf("conv_infos = %s\n", s2);
				print_data(datas);
				s1 = ft_strjoin_free(s1, s2, 1, 1);
				// format++;
//			translate(s2);
			}
		}
	va_end(args);
	return (1);
}

int main()
{
//	if (argc == 2)
//		printf("%s\n", argv[1]);
	// ft_printf("salut toi % +10d, puis %c", 5, 'g');
	// ft_printf("|%-+.20d|\n\n", 12);
	// ft_printf("4567 |%-10]5d| plip\n", 12);
	// ft_printf("4567 |%10]5d| plip\n", 12);
	// ft_printf("|%10.5d|\n", -12);
	// ft_printf("|%10d|\n", -12);
	// ft_printf("|%010d|\n", -12);
	// ft_printf("|%-10.5d|\n", -12);
	// ft_printf("|%-010.5d|\n", -12);

	printf("|%-+.20d|\n\n", 12);
	printf("4567 |%-10]5d| plip\n", 12);
	printf("4567 |%10]5d| plip\n", 12);
	printf("|%10.5d|\n", -12);
	printf("|%10d|\n", -12);
	printf("|%010d|\n", -12);
	printf("|%-10.5d|\n", -12);
	printf("|%-010.5d|\n", -12);
//	printf("%+ d", 5);
	return (0);
}
