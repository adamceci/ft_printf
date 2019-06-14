#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
int		*convert_base(int value, int base, int *i)
{
	int		*rest;
	int		num;
	int		size;

	num = value;
	while (num > 0)
	{
		*i++;
		size++;
		num /= base;
	}
	rest = (int*)malloc(sizeof(*rest) * size);
	while (value > 0)
	{
		rest[size - 1] = num % base;
		num / base;
		size--;
	}
	return (rest);
}
*/
char	*ft_itoa_base(int value, int base)
{
	char	*str;
	int		i;
	int		sign;
	int		num;
	int		rest;

	sign = 0;
	i = 0;
	if (base == 10 && value < 0)
	{
		sign = 1;
		value *= -1;
		i++;
	}
	num = value;
	while (num > 0)
	{
		i++;
		num /= base;
	}
	str = (char*)malloc(sizeof(*str) * i + 1);
	str[i] = '\0';
	while (value > 0)
	{
		rest = value % base;
		if (rest >= 0 && rest <= 9)
			str[i - 1] = rest + '0';
		else
			str[i - 1] = rest - 10 + 'A';
		value /= base;
		i--;
	}
	if (sign)
		str[0] = '-';
	return (str);
}

int		main()
{
	char	*str;

	str = ft_itoa_base(10540, 15);
	printf("%s\n", str);
	return (0);
}
