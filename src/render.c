#include "cub3d.h"
#include "mlx.h"
#include <math.h>

void	fill_floor_and_ceiling(t_game *game)
{
	int	h;
	int	w;

	if (!game)
		return ;
	h = 0;
	while (h < game->scr_img.height / 2)
	{
		w = 0;
		while (w < game->scr_img.width)
		{
			game->scr_img.addr[h * game->scr_img.width + w] = \
				game->texture.ceiling;
			w++;
		}
		h++;
	}
	while (h < game->scr_img.height)
	{
		w = 0;
		while (w < game->scr_img.width)
		{
			game->scr_img.addr[h * game->scr_img.width + w] = \
				game->texture.floor;
			w++;
		}
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
		game->ray.a_map.ax = (int) game->player.pos.x;
		game->ray.a_map.ay = (int) game->player.pos.y;
		game->ray.d_dist.x = fabs(1 / game->ray.dir.x);
		game->ray.d_dist.y = fabs(1 / game->ray.dir.y);
		send_ray(game, i);
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->scr_img.img, 0, 0);
}

void	set_direction(t_game *game)
{
	if (game->ray.dir.x < 0)
	{
		game->ray.a_step.ax = -1;
		game->ray.s_dist.x = (game->player.pos.x - game->ray.a_map.ax)
			* game->ray.d_dist.x;
	}
	else
	{
		game->ray.a_step.ax = 1;
		game->ray.s_dist.x = (game->ray.a_map.ax + 1.0 - game->player.pos.x)
			* game->ray.d_dist.x;
	}
	if (game->ray.dir.y < 0)
	{
		game->ray.a_step.ay = -1;
		game->ray.s_dist.y = (game->player.pos.y - game->ray.a_map.ay)
			* game->ray.d_dist.y;
	}
	else
	{
		game->ray.a_step.ay = 1;
		game->ray.s_dist.y = (game->ray.a_map.ay + 1.0 - game->player.pos.y)
			* game->ray.d_dist.y;
	}
}

void	set_wall_hit(t_game *game)
{
	game->ray.wall = 0;
	while (!game->ray.wall)
	{
		if (game->ray.s_dist.x < game->ray.s_dist.y)
		{
			game->ray.s_dist.x += game->ray.d_dist.x;
			game->ray.a_map.ax += game->ray.a_step.ax;
			game->ray.side = 0;
		}
		else
		{
			game->ray.s_dist.y += game->ray.d_dist.y;
			game->ray.a_map.ay += game->ray.a_step.ay;
			game->ray.side = 1;
		}
		if (game->map.map[game->ray.a_map.ax][game->ray.a_map.ay] == M_WALL)
			game->ray.wall = 1;
	}
}

void	set_ray_dist(t_game *game)
{
	printf("%f\n", game->ray.s_dist.x);
	printf("%f\n", game->ray.s_dist.y);
	if (game->ray.side == 0)
		game->ray.perp_wall_dist = game->ray.s_dist.x - game->ray.d_dist.x;
	else
		game->ray.perp_wall_dist = game->ray.s_dist.y - game->ray.d_dist.y;
	printf("%f\n", game->ray.perp_wall_dist);
	if (game->ray.perp_wall_dist < 0.001)
		game->ray.perp_wall_dist += 0.001;
	game->ray.line_height = (int) (WIN_Y / game->ray.perp_wall_dist * 2);
	game->ray.draw_start = -game->ray.line_height / 2 + WIN_Y / 2;
	if (game->ray.draw_start < 0)
		game->ray.draw_start = 0;
	game->ray.draw_end = game->ray.line_height / 2 + WIN_Y / 2;
	if (game->ray.draw_end >= WIN_Y)
		game->ray.draw_end = WIN_Y - 1;
}


void	send_ray(t_game *game, int i)
{
	set_direction(game);
	set_wall_hit(game);
	set_ray_dist(game);
	draw_wall_side(game, i);
}
