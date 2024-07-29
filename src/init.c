#include "cub3d.h"
#include "libft.h"
#include "mlx.h"
#include <fcntl.h>

t_err	map_init(t_game *game, const char *path)
{
	char	*line;
	int		fd;

	if (!game || !path)
		return (perr(ESTR_ASSERT_));
	if (!file_ext_validate(path, FILE_EXT_MAP))
		return (perr("invalid map file extention"));
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (perr("map file cannot be opened"));
	game->map.data = ft_strdup("");
	if (!game->map.data)
		return (close(fd), perr("map game->map.data cannot be allocated"));
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		game->map.data = ft_strjoin_gnl(game->map.data, line);
		if (!game->map.data)
			return (free(line), close(fd), perr("map buff cannot be joined"));
		free(line);
	}
	return (close(fd), SUCCESS);
}

t_err	mlx_init_x(t_game *game)
{
	if (!game)
		return (perr(ESTR_ASSERT_));
	game->mlx = mlx_init();
	if (!game->mlx)
		return (perr("mlx cannot be initialized"));
	game->win = mlx_new_window(game->mlx, WIN_X, WIN_Y, WIN_T);
	if (!game->win)
		return (perr("mlx window cannot be opened"));
	return (SUCCESS);
}

t_err	scr_img_init(t_game *game)
{
	if (!game || !game->mlx)
		return (perr(ESTR_ASSERT_));
	game->scr_img.img = mlx_new_image(game->mlx, WIN_X, WIN_Y);
	if (!game->scr_img.img)
		return (perr("screen image cannot be initialized"));
	game->scr_img.addr = (int *) mlx_get_data_addr(game->scr_img.img,
		&game->scr_img.bits_per_pixel,
		&game->scr_img.size_line,
		&game->scr_img.endian);
	if (!game->scr_img.addr)
		return (mlx_destroy_image(game->mlx, game->scr_img.img),
			perr("screen image data cannot be initialized"));
	game->scr_img.width = WIN_X;
	game->scr_img.height = WIN_Y;
	return (SUCCESS);
}

t_err	mlx_hook_init_x(t_game *game)
{
	if (!game || !game->map.map || !game->mlx || !game->win)
		return (perr(ESTR_ASSERT_));
	mlx_do_key_autorepeatoff(game->mlx);
	mlx_hook(game->win, ON_QUIT_TAP, 0, on_game_quit, game);
	mlx_hook(game->win, 2, (1L << 0), on_key_press, game);
	mlx_hook(game->win, 3, (1L << 1), on_key_release, game);
	// game->resolution = game->textures[0].width;
	mlx_loop_hook(game->mlx, on_loop, game);
}
