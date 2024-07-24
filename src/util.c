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

void	str_arr_dispose(char **arr)
{
	char	**iter;
	size_t	i;

	i = 0;
	iter = arr;
	while (iter[i])
	{
		free(iter[i]);
		iter[i] = NULL;
		i++;
	}
	free(arr);
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

int	is_not_digit_x(unsigned int idx, char *curr, void *param)
{
	(void)idx;
	(void)param;
	return (!ft_isdigit(*curr));
}

bool	rgb_validate(int rgb[3])
{
	if (!rgb)
		return (false);
	return (rgb[0] < 255 &&
			rgb[1] < 255 &&
			rgb[2] < 255 &&
			rgb[0] > 0 &&
			rgb[1] > 0 &&
			rgb[2] > 0);
}
