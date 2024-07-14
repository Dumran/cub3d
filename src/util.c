#include "cub3d.h"
#include <math.h>

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

char	*ft_strrtrim(const char *s1, const char *set)
{
	size_t	i;

	if (!s1 || !set)
		return (0);
	i = ft_strlen(s1);
	while (i && ft_strchr(set, s1[i]))
		i--;
	return (ft_substr(s1, 0, i + 1));
}

int	is_valid_vertical_edge_char(unsigned int idx, char *c, void *p)
{
	(void)p;
	(void)idx;
	return (*c != '1' && *c != ' ');
}

int	ft_strany(char *s, int (*f)(unsigned int idx, char *str, void *ptr), void *pass)
{
	unsigned int	i;

	i = 0;
	if (!(*s) || !f)
		return (0);
	while (s[i])
	{
		if (f(i, &s[i], pass))
			return (1);
		i++;
	}
	return (0);
}

int	is_able_to_be_surrounded(unsigned int idx, char *c, void *p)
{
	(void)p;
	(void)idx;
	return (*c == M_FLOOR || \
		*c == M_NORTH || \
		*c == M_SOUTH || \
		*c == M_EAST || \
		*c == M_WEST);
}

bool	is_valid_edge_char(const char *const row)
{
	return (!(row[0] == M_FLOOR || \
			row[0] == M_NORTH || \
			row[0] == M_SOUTH || \
			row[0] == M_EAST || \
			row[0] == M_WEST || \
			row[ft_strlen(row) - 1] == M_FLOOR || \
			row[ft_strlen(row) - 1] == M_NORTH || \
			row[ft_strlen(row) - 1] == M_SOUTH || \
			row[ft_strlen(row) - 1] == M_EAST || \
			row[ft_strlen(row) - 1] == M_WEST));
}

double	deg_to_rad(double degree)
{
	return (degree * M_PI / 180.0);
}
