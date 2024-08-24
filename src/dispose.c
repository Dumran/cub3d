#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>

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
	mlx_destroy_image(game->mlx, game->texture.north.img);
	mlx_destroy_image(game->mlx, game->texture.west.img);
	mlx_destroy_image(game->mlx, game->texture.south.img);
	mlx_destroy_image(game->mlx, game->texture.east.img);
	if (game->scr_img.img)
		mlx_destroy_image(game->mlx, game->scr_img.img);
}

void	map_dispose(t_map *map)
{
	if (!map)
		return ;
	free(map->data);
	while (*map->map)
		printf("map: %s\n", *map->map++);
	while (*map->lines)
		printf("%s\n", *map->lines++);
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
}
