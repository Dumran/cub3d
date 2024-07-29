#include "cub3d.h"
#include <math.h>

void	key_left(t_game *game)
{
	double	dir_x;
	double	plane_x;

	dir_x = game->player.dir.x;
	game->player.dir.x = game->player.dir.x * cos(G_ROTATE_S) -
		game->player.dir.y * sin(G_ROTATE_S);
	game->player.dir.y = dir_x * sin(G_ROTATE_S) +
		game->player.dir.y * cos(G_ROTATE_S);
	plane_x = game->ray.plane.x;
	game->ray.plane.x = game->ray.plane.x * cos(G_ROTATE_S) -
		game->ray.plane.y * sin(G_ROTATE_S);
	game->ray.plane.y = plane_x * sin(G_ROTATE_S) +
		game->ray.plane.y * cos(G_ROTATE_S);
}

void	key_right(t_game *game)
{
	double	dir_x;
	double	plane_x;

	dir_x = game->player.dir.x;
	game->player.dir.x = game->player.dir.x * cos(-G_ROTATE_S) -
		game->player.dir.y * sin(-G_ROTATE_S);
	game->player.dir.y = dir_x * sin(-G_ROTATE_S) +
		game->player.dir.y * cos(-G_ROTATE_S);
	plane_x = game->ray.plane.x;
	game->ray.plane.x = game->ray.plane.x * cos(-G_ROTATE_S) -
		game->ray.plane.y * sin(-G_ROTATE_S);
	game->ray.plane.y = plane_x * sin(-G_ROTATE_S) +
		game->ray.plane.y * cos(-G_ROTATE_S);
}
