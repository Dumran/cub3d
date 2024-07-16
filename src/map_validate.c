#include "cub3d.h"
#include <math.h>

t_err	player_detect(t_state *s, char *row, size_t i)
{
	if (s->ray->player.x)
		return (perr("invalid player count"));
	s->ray->player.y = i;
	s->ray->player.x = ft_lstsize(s->map->map);
	s->ray->player_dir_degree = (int const [UINT8_MAX]){ \
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

t_char_type	char_type_get(char const c)
{
	if (c == '1')
		return (CHR_FRAME);
	else if (c == ' ')
		return (CHR_SPACE);
	else if (c == '0' || \
			c == 'N' || \
			c == 'S' || \
			c == 'E' || \
			c == 'W')
		return (CHR_SURROUNDABLE);
	return (CHR_INVALID);
}

t_err	map_validate_surroundings(char *row, char *prev, size_t prev_len, size_t i)
{
	t_char_type	curr;
	t_char_type	v_prev;
	t_char_type	h_next;

	curr = char_type_get(row[i]);
	h_next = char_type_get(row[i + 1]);
	if ((prev_len - 1) < i)
		v_prev = CHR_INVALID;
	else
		v_prev = char_type_get(prev[i]);
	if (curr == CHR_INVALID)
		return (perr("invalid char on map"));
	if (curr == CHR_SPACE)
		if ((h_next == CHR_SURROUNDABLE) || (v_prev == CHR_SURROUNDABLE))
			return (perr("invalid char on map"));
	if (curr == CHR_SURROUNDABLE)
		if (h_next == CHR_SPACE || v_prev == CHR_SPACE || v_prev == CHR_INVALID)
			return (perr("invalid char on map"));
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
		if (map_validate_surroundings(row, prev, prev_len, i))
			return (FAILURE);
	}
	if (prev_len > ++i)
		if (ft_strany(prev + i, is_able_to_be_surrounded, NULL))
			return (perr("invalid map"));
	return (SUCCESS);
}
