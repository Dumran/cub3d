#include "cub3d.h"

size_t	ft_arrlen(void *arr)
{
	int	i;

	i = 0;
	while (((void **) arr)[i])
		i++;
	return (i);
}

size_t	ft_arrfree_2d(void *arr)
{
	int	i;

	i = 0;
	while (((void **) arr)[i])
		free(((void **) arr)[i++]);
	free(arr);
}

int	ft_strevery(char *s, int (*f)(unsigned int, char *, void *), void *pass)
{
	unsigned int	i;

	i = 0;
	if (!(*s) || !f)
		return (0);
	while (s[i])
	{
		if (!f(i, &s[i], pass))
			return (0);
		i++;
	}
	return (1);
}

int	ft_isdigit_x(unsigned int idx, char *curr, void *param)
{
	(void)idx;
	(void)param;
	return (*curr >= '0' && *curr <= '9');
}
