#include "cub3d.h"
#include <math.h>

t_err	player_detect(t_state *s, char *row, size_t i)
{
	if (s->ray->player.x)
		return (perr("invalid player count"));
	s->ray->player.y = i;
	s->ray->player.x = ft_lstsize(s->map.map);
	s->ray->player_dir_degree = (int const [UINT8_MAX]){\
		['N'] = DEG_N, ['E'] = DEG_E, ['S'] = DEG_S, ['W'] = DEG_W} \
		[(int)row[i]];
	s->ray->player.y += 0.5;
	s->ray->player.x += 0.5;
	s->ray->dir.x = cos(deg_to_rad(s->ray->player_dir_degree));
	s->ray->dir.y = sin(deg_to_rad(s->ray->player_dir_degree));
	s->ray->plane.x = s->ray->dir.y * FOV;
	s->ray->plane.y = -s->ray->dir.x * FOV;
	row[i] = M_FLOOR;
	return (SUCCESS);
}

t_err	map_validate_row_mid(t_state *s, char *row, char *prev)
{
	const size_t	prev_len = ft_strlen(prev);
	size_t			i;

	if (is_valid_edge_char(row))
		return (perr("invalid map near to first or last"));
	i = 0;
	while (row[++i + 1])
	{
		if ((row[i] == M_NORTH || row[i] == M_SOUTH ||
			row[i] == M_EAST || row[i] == M_WEST))
			if (player_detect(s, row, i))
				return (FAILURE);
		// here
		if (check_relative(prev_len, row, prev, i))
			return (FAILURE);
	}
}
