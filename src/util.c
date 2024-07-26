#include "cub3d.h"
#include "libft.h"

int	is_not_digit_x(unsigned int idx, char *curr, void *param)
{
	(void)idx;
	(void)param;
	return (!ft_isdigit(*curr));
}

int	is_not_x_or_one(unsigned int idx, char *curr, void *param)
{
	(void)idx;
	(void)param;
	return (*curr != '1' && *curr != 'X');
}

int	is_not_x_or_one_vertical(unsigned int idx, char *curr, void *param)
{
	(void)idx;
	(void)param;
	return ((idx == 0 && *curr != '1') && (*curr && !*(curr + 1) && *curr != 'X'));
}

bool	rgb_validate(int rgb[3])
{
	if (!rgb)
		return (false);
	return (rgb[0] <= 255 &&
			rgb[1] <= 255 &&
			rgb[2] <= 255 &&
			rgb[0] >= 0 &&
			rgb[1] >= 0 &&
			rgb[2] >= 0);
}
