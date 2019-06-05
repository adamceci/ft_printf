/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceciora <aceciora@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 17:19:09 by aceciora          #+#    #+#             */
/*   Updated: 2019/06/05 19:27:44 by aceciora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

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
		datas->min_field = get_numberi((const char*)&str[*i], i);
		(*i)--;
	}
	else if (str[*i] == '.')
	{
		(*i)++;
		datas->precision = get_numberi((const char*)&str[*i], i);
		(*i)--;
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

char	*conv_X(t_print *datas, va_list args)
{
	// TODO
	printf("hey X");
	return (NULL);
}

char	*conv_c(t_print *datas, va_list args)
{
	// TODO
	printf("hey c");
	return (NULL);
}

char	*conv_d(t_print *datas, va_list args)
{
	// TODO
	printf("hey d");
	int		value;
	char	*str;

	value = va_arg(args, int);
	str = ft_itoa(value);
	return (str);
}

char	*conv_f(t_print *datas, va_list args)
{
	printf("hey f");
	// TODO
	return (NULL);
}

char	*conv_i(t_print *datas, va_list args)
{
	printf("hey i");
	// TODO
	return (NULL);
}

char	*conv_o(t_print *datas, va_list args)
{
	printf("hey o");
	// TODO
	return (NULL);
}

char	*conv_p(t_print *datas, va_list args)
{
	printf("hey p");
	// TODO
	return (NULL);
}

char	*conv_s(t_print *datas, va_list args)
{
	printf("hey s");
	// TODO
	return (NULL);
}

char	*conv_u(t_print *datas, va_list args)
{
	printf("hey u");
	// TODO
	return (NULL);
}

char	*conv_x(t_print *datas, va_list args)
{
	printf("hey x");
	// TODO
	return (NULL);
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

void init_struct(t_print *datas)
{
	datas->minus_f = 0;
	datas->plus_f = 0;
	datas->hash_f = 0;
	datas->zero_f = 0;
	datas->space_f = 0;
	datas->min_field = -1;
	datas->precision = -1;
	datas->conversion = '0';
}

void print_data(t_print datas)
{
	printf("- = %d\n+ = %d\n# = %d\n0 = %d\n' ' = %d\nfield = %d\npreci = %d\nconv = %c\n",
					datas.minus_f, datas.plus_f, datas.hash_f, datas.zero_f, datas.space_f,
					datas.min_field, datas.precision, datas.conversion);
	printf("\n");
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
			datas->precision = -1;
	}
	if (numeric_conversion(datas->conversion))
	{
		if (datas->zero_f && datas->precision != -1)
			datas->zero_f = 0;
		if (datas->minus_f && datas->zero_f)
			datas->zero_f = 0;
		if (datas->plus_f && datas->space_f)
			datas->space_f = 0;
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
		// /!\ IF NO '%' --> COUNT_UNTIL RETURNS 0 !!
		s1 = ft_strjoin_free(s1, ft_strsub(format, 0, i), 1, 1);
		format += i;
		if (*format++ == '%')
		{
			init_struct(&datas);
			s2 = conv_infos((char**)&format);
			parse(s2, &datas);
			free(s2);
			flag_priorities(&datas);
			s2 = translate(&datas, args);
			s1 = ft_strjoin_free(s1, s2, 1, 1);
			printf("format = %s\n", format);
		}
	}
	va_end(args);
	ft_putstr(s1);
	return (ft_strlen(s1));
}

int main()
{
	// if (argc == 2)
	ft_printf("pourquoi %d %s\n", 5, "hujiw");
	// ft_printf("salut toi % +10d, puis %c", 5, 'g');
	//
	// ft_printf("|%-+.20d|\n\n", 12);
	// ft_printf("4567 |%-10]5d| plip\n", 12);
	// ft_printf("4567 |%10]5d| plip\n", 12);
	// ft_printf("|%10.5d|\n", -12);
	// ft_printf("|%10d|\n", -12);
	// ft_printf("|%010d|\n", -12);
	// ft_printf("|%-10.5d|\n", -12);
	// ft_printf("|%-010.5d|\n", -12);
	//
	// printf("|%-+.20d|\n\n", 12);
	// printf("4567 |%-10]5d| plip\n", 12);
	// printf("4567 |%10]5d| plip\n", 12);
	// printf("|%10.5d|\n", -12);
	// printf("|%10d|\n", -12);
	// printf("|%010d|\n", -12);
	// printf("|%-10.5d|\n", -12);
	// printf("|%-010.5d|\n", -12);
	//
	// printf("%p\n", "c");
	// printf("%+p\n", "heeey");
	// printf("%#p\n", "heeey");
	// printf("%0p\n", "heeey");
	// printf("% p\n", "heeey");
	// printf("%040p\n", "heeey");
	// printf("%.1p\n", "heeey");
	return (0);
}
