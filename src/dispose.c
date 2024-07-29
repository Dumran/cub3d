#include "cub3d.h"
#include "mlx.h"

void	game_dispose(t_game *game)
{
	if (!game)
		return ;
	map_dispose(&game->map);
	texture_dispose(game);
	if (game->mlx && game->win)
		mlx_destroy_window(game->mlx, game->win);
}

void	texture_dispose(t_game *game)
{
	if (!game)
		return ;
	mlx_destroy_image(game->mlx, game->texture.north.addr);
	mlx_destroy_image(game->mlx, game->texture.west.addr);
	mlx_destroy_image(game->mlx, game->texture.south.addr);
	mlx_destroy_image(game->mlx, game->texture.east.addr);
	if (game->scr_img.img)
		mlx_destroy_image(game->mlx, game->scr_img.img);
}

void	map_dispose(t_map *map)
{
	int	i;

	if (!map)
		return ;
	free(map->data);
	str_arr_dispose(map->map);
	str_arr_dispose(map->lines);
}

void	str_arr_dispose(char **arr)
{
	char	**iter;
	size_t	i;

	i = 0;
	iter = arr;
	while (iter[i])
	{
		free(iter[i]);
		iter[i] = NULL;
		i++;
	}
	free(arr);
}
