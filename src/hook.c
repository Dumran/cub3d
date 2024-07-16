#include "cub3d.h"
#include <mlx.h>

int	on_quit_game(t_state *s)
{
	map_clear(s);
	textures_dispose(s);
	exit(SUCCESS);
	return (0);
}

int	on_key_press(int keycode, t_state *s)
{
	if (keycode == KEY_ESC || keycode == KEY_Q)
		on_quit_game(s);
	if (keycode == KEY_W)
		s->player_keys[KEY_IDX_W] = 1;
	if (keycode == KEY_A)
		s->player_keys[KEY_IDX_A] = 1;
	if (keycode == KEY_S)
		s->player_keys[KEY_IDX_S] = 1;
	if (keycode == KEY_D)
		s->player_keys[KEY_IDX_D] = 1;
	if (keycode == KEY_LEFT)
		s->player_keys[KEY_IDX_LARROW] = 1;
	if (keycode == KEY_RIGHT)
		s->player_keys[KEY_IDX_RARROW] = 1;
	return (0);
}

int	on_key_release(int keycode, t_state *s)
{
	if (keycode == KEY_W)
		s->player_keys[KEY_IDX_W] = 0;
	if (keycode == KEY_A)
		s->player_keys[KEY_IDX_A] = 0;
	if (keycode == KEY_S)
		s->player_keys[KEY_IDX_S] = 0;
	if (keycode == KEY_D)
		s->player_keys[KEY_IDX_D] = 0;
	if (keycode == KEY_LEFT)
		s->player_keys[KEY_IDX_LARROW] = 0;
	if (keycode == KEY_RIGHT)
		s->player_keys[KEY_IDX_RARROW] = 0;
	return (0);
}

void	on_move(t_state *s)
{
	if (s->player_keys[KEY_IDX_W])
		key_w(s);
	if (s->player_keys[KEY_IDX_A])
		key_a(s);
	if (s->player_keys[KEY_IDX_S])
		key_s(s);
	if (s->player_keys[KEY_IDX_D])
		key_d(s);
	if (s->player_keys[KEY_IDX_LARROW])
		key_left(s);
	if (s->player_keys[KEY_IDX_RARROW])
		key_right(s);
}

int		on_loop(void *p)
{
	t_state *s;

	s = (t_state *) p;
	fill_floor_and_ceiling(s);
	on_move(s);
	on_ray_casting(s);
	mlx_put_image_to_window(s->mlx, s->win, s->win_img.img, 0, 0);
	return (0);
}

void	hook_init(t_state *s)
{
	mlx_do_key_autorepeatoff(s->mlx);
	mlx_hook(s->win, ON_DESTROY, 0, on_quit_game, s);
	mlx_hook(s->win, 2, (1L << 0), on_key_press, s);
	mlx_hook(s->win, 3, (1L << 1), on_key_release, s);
	s->resolution = s->images[0].width;
	mlx_loop_hook(s->mlx, on_loop, s);
}
