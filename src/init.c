#include "cub3d.h"
#include "libft.h"
#include "mlx.h"
#include <fcntl.h>

t_err	game_init(t_game *game, const char *path)
{
	t_err	err;

	if (!game || !path)
		return (perr(ESTR_ASSERT_));
	err = mlx_init_x(game);
	if (err)
		return (FAILURE);
	err = map_init(game, path);
	if (err)
		return (FAILURE);
	err = scr_img_init(game);
	if (err)
		return (FAILURE);
	return (SUCCESS);
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

t_err	map_init(t_game *game, const char *path)
{
	char	*buff;
	char	*line;
	int		fd;

	if (!game || !path)
		return (perr(ESTR_ASSERT_));
	if (!file_ext_validate(path, FILE_EXT_MAP))
		return (perr("invalid map file extention"));
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (perr("map file cannot be opened"));
	buff = ft_strdup("");
	if (!buff)
		return (close(fd), perr("map buffer cannot be allocated"));
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		buff = ft_strjoin_gnl(buff, line);
		if (!buff)
			return (free(line), close(fd), perr("map buff cannot be joined"));
		free(line);
	}
	return (game->map.data = buff, close(fd), SUCCESS);
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
