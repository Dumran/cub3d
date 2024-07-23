#include "cub3d.h"

t_err	game_init(t_game *game, const char *path)
{
	t_err	err;

	if (!game || !path)
		return (perr(ESTR_ASSERT_));
	err = mlx_init_x(game);
	if (err)
		return (FAILURE);
}

t_err	mlx_init_x(t_game *game)
{
	
}
