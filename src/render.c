#include "cub3d.h"

void	fill_floor_and_ceiling(t_game *game)
{
	size_t	h;
	size_t	w;

	if (!game)
		return ;
	h = 0;
	while (h < game->scr_img.height / 2)
	{
		w = 0;
		while (w < game->scr_img.width)
			game->scr_img.addr[h * game->scr_img.width + w++] = \
				game->texture.ceiling; // might get error
		h++;
	}
	while (h < game->scr_img.height)
	{
		w = 0;
		while (w < game->scr_img.width)
			game->scr_img.addr[h * game->scr_img.width + w++] = \
				game->texture.ceiling;
		h++;
	}
}

void	ray_casting(t_game *game)
{
	size_t	i;

	if (!game)
		return ;
	i = 0;
	while (i < WIN_X)
	{
		game->ray.camera_x = 2 * i / (double) WIN_X - 1;
		game->ray.dir.x = game->player.dir.x + game->ray.plane.x
			* game->ray.camera_x;
		game->ray.dir.y = game->player.dir.y + game->ray.plane.y
			* game->ray.camera_x;
		game->ray.a_map.x = (int) game->player.pos.x;
		game->ray.a_map.y = (int) game->player.pos.y;
		game->ray.d_dist.x = fabs(1 / game->ray.dir.x);
		game->ray.d_dist.y = fabs(1 / game->ray.dir.y);
		// send_ray(game, i);
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->scr_img, 0, 0);
}
