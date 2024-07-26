#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

t_err	game_load(t_game *game)
{
	t_err	err;
	size_t	row;

	if (!game || !game->map.data)
		return (perr(ESTR_ASSERT_));
	row = 0;
	game->map.lines = map_split_line(game->map.data);
	if (!game->map.lines)
		return (FAILURE);
	err = map_meta_load(game, &row);
	if (err)
		return (FAILURE);
	err = map_data_load(game, &row);
	if (err)
		return (FAILURE);
	err = map_data_validate(game);
	if (err)
		return (FAILURE);
	return (SUCCESS);
}

