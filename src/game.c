#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

t_err	game_init(t_game *game, const char *path)
{
	t_err	err;

	if (!game || !path)
		return (perr(ESTR_ASSERT_));
	err = map_init(game, path);
	if (err)
		return (FAILURE);
	err = mlx_init_x(game);
	if (err)
		return (FAILURE);
	err = scr_img_init(game);
	if (err)
		return (FAILURE);
	return (SUCCESS);
}

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
	err = mlx_hook_init_x(game);
	if (err)
		return (FAILURE);
	return (SUCCESS);
}

t_err	game_loop(t_game *game)
{
	if (!game || !game->map.map)
		return (perr(ESTR_ASSERT_));
	mlx_loop(game->mlx);
	return (FAILURE);
}
