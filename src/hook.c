#include "cub3d.h"

int	on_game_quit(t_game *game)
{
	if (!game)
		return (-1);
	game_dispose(game);
	exit(0);
	return (0);
}

int	on_loop(void *param)
{
	t_game *game;

	game = (t_game *) param;
	if (!game)
		return (-1);
	fill_floor_and_ceiling(game);
	on_move(game);
	ray_casting(game);
	mlx_put_image_to_window(game->mlx, game->win, game->scr_img.img, 0, 0);
	return (0);
}

int	on_move(t_game *game)
{
	if (!game)
		return (-1);
	if (game->player.keys[IDX_KEY_W])
		key_w(game);
	if (game->player.keys[IDX_KEY_A])
		key_a(game);
	if (game->player.keys[IDX_KEY_S])
		key_s(game);
	if (game->player.keys[IDX_KEY_D])
		key_d(game);
	if (game->player.keys[IDX_KEY_LEFT])
		key_left(game);
	if (game->player.keys[IDX_KEY_RIGHT])
		key_right(game);
	return (0);
}

int	on_key_press(const int keycode, t_game *game)
{
	if (!game)
		return (-1);
	if (keycode == KEY_ESC || keycode == KEY_Q)
		on_game_quit(game);
	if (keycode == KEY_W)
		game->player.keys[IDX_KEY_W] = 1;
	if (keycode == KEY_A)
		game->player.keys[IDX_KEY_A] = 1;
	if (keycode == KEY_S)
		game->player.keys[IDX_KEY_S] = 1;
	if (keycode == KEY_D)
		game->player.keys[IDX_KEY_D] = 1;
	if (keycode == KEY_LEFT)
		game->player.keys[IDX_KEY_LEFT] = 1;
	if (keycode == KEY_RIGHT)
		game->player.keys[IDX_KEY_RIGHT] = 1;
	return (0);
}

int	on_key_release(const int keycode, t_game *game)
{
	if (!game)
		return (-1);
	if (keycode == KEY_W)
		game->player.keys[IDX_KEY_W] = 0;
	if (keycode == KEY_A)
		game->player.keys[IDX_KEY_A] = 0;
	if (keycode == KEY_S)
		game->player.keys[IDX_KEY_S] = 0;
	if (keycode == KEY_D)
		game->player.keys[IDX_KEY_D] = 0;
	if (keycode == KEY_LEFT)
		game->player.keys[IDX_KEY_LEFT] = 0;
	if (keycode == KEY_RIGHT)
		game->player.keys[IDX_KEY_RIGHT] = 0;
	return (0);
}
