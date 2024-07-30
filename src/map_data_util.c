#include "cub3d.h"

bool	map_data_validate_char(t_game *game)
{
	size_t	i;
	size_t	j;

	if (!game || !game->map.map)
		return (false);
	i = 0;
	while (game->map.map[i])
	{
		j = 0;
		while (game->map.map[i][j])
		{
			if (!str_include(W_MAP_SET, game->map.map[i][j]))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

void	map_data_set_direction(t_game *game, const char c)
{
	if (c == M_NORTH)
	{
		game->player.dir.x = -1;
		game->player.dir.y = 0;
	}
	else if (c == M_SOUTH)
	{
		game->player.dir.x = 1;
		game->player.dir.y = 0;
	}
	else if (c == M_WEST)
	{
		game->player.dir.x = 0;
		game->player.dir.y = -1;
	}
	else if (c == M_EAST)
	{
		game->player.dir.x = 0;
		game->player.dir.y = 1;
	}
}

void	map_data_set_plane(t_game *game, const char c)
{
	if (c == M_NORTH)
	{
		game->ray.plane.x = 0;
		game->ray.plane.y = 0.66;
	}
	else if (c == M_SOUTH)
	{
		game->ray.plane.x = 0;
		game->ray.plane.y = -0.66;
	}
	else if (c == M_WEST)
	{
		game->ray.plane.x = -0.66;
		game->ray.plane.y = 0;
	}
	else if (c == M_EAST)
	{
		game->ray.plane.x = 0.66;
		game->ray.plane.y = 0;
	}
}

void	map_data_get_direction(t_game *game, const char c)
{
	map_data_set_direction(game, c);
	map_data_set_plane(game, c);
}

int	map_data_count_player(t_game *game)
{
	int	count;
	int	i;
	int	j;

	i = 0;
	count = 0;
	while (game->map.map[i])
	{
		j = 0;
		while (game->map.map[i][j])
		{
			if (str_include(W_PLAYER_SET, game->map.map[i][j]))
			{
				game->player.pos.x = i + 0.5;
				game->player.pos.y = j + 0.5;
				map_data_get_direction(game, game->map.map[i][j]);
				count++;
			}
			j++;
		}
		i++;
	}
	return (count);
}
