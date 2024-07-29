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
				count++;
			j++;
		}
		i++;
	}
	return (count);
}
