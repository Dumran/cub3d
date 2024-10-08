#include "cub3d.h"
#include "libft.h"
#include <stdlib.h>

size_t	str_arr_len(char **arr)
{
	size_t	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

bool	ft_isspace(const int c)
{
	return (c == ' ' ||
			c == '\t' ||
			c == '\n' ||
			c == '\v' ||
			c == '\f' ||
			c == '\r');
}

char	*ft_strtrim_x(const char *str, const char *set)
{
	char	*buff;

	if (!str || !set)
		return (NULL);
	buff = ft_strtrim(str, set);
	free((void *)str);
	return (buff);
}

int	strany(char *s, int (*f)(unsigned int idx, char *str, void *p), void *pass)
{
	unsigned int	i;

	if (!(*s) || !f)
		return (0);
	i = 0;
	while (s[i])
	{
		if (f(i, &s[i], pass))
			return (1);
		i++;
	}
	return (0);
}


bool	str_include(const char *str, const char c)
{
	size_t	i;

	if (!str)
		return (false);
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (true);
		i++;
	}
	return (false);
}
