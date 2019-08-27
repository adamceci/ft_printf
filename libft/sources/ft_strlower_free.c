#include "libft.h"

char				*ft_strlower_free(char *str, int free1)
{
	unsigned int	i;
	char			*s;

	s = NULL;
	if (str)
	{
		s = ft_strnew(ft_strlen(str));
		if (!s)
			return (NULL);
		i = 0;
		while (str[i])
		{
			s[i] = ft_tolower(str[i]);
			i++;
		}
	}
    if (free1)
        free(str);
	return (s);
}