#include "cub3d.h"
#include "mlx.h"
#include "libft.h"

t_err	texture_set_value(t_game *game, t_meta key, char *value)
{
	if (!game || !value || key == META_END)
		return (perr(ESTR_ASSERT_));
	if (key == META_NO)
		if (img_load(game, &game->texture.north, value))
			return (FAILURE);
	if (key == META_WE)
		if (img_load(game, &game->texture.west, value))
			return (FAILURE);
	if (key == META_EA)
		if (img_load(game, &game->texture.east, value))
			return (FAILURE);
	if (key == META_SO)
		if (img_load(game, &game->texture.south, value))
			return (FAILURE);
	if (key == META_C)
		if (color_load(game, &game->texture.ceiling, value))
			return (FAILURE);
	if (key == META_F)
		if (color_load(game, &game->texture.floor, value))
			return (FAILURE);
	return (SUCCESS);
}

t_err	img_load(t_game *game, t_img *img, char *path)
{
	if (!game || !img || !path)
		return (perr(ESTR_ASSERT_));
	img->img = mlx_xpm_file_to_image(game->mlx, path,
		&img->width, &img->height);
	if (!img->img)
		return (perr("xpm to image error"));
	img->addr = (int *) mlx_get_data_addr(img->img,
		&img->bits_per_pixel,
		&img->size_line,
		&img->endian);
	if (!img->addr)
		return (mlx_destroy_image(game->mlx, img->img),
			perr("img addr cannot be got"));
	return (SUCCESS);
}

t_err	color_load(t_game *game, int *color, char *rgb_str)
{
	char	**rgb_arr;
	int		rgb[3];

	if (!game || !color || !rgb_str)
		return (perr(ESTR_ASSERT_));
	rgb_str = ft_strtrim(rgb_str + 2, W_SPACE_SET);
	if (!rgb_str)
		return (perr("map color data cannot be trimmed"));
	rgb_arr = ft_split(rgb_str, ',');
	if (!rgb_arr)
		return (FAILURE);
	if (str_arr_len(rgb_arr) != 3)
		return (str_arr_dispose(rgb_arr), FAILURE);
	if (strany(rgb_arr[0], is_not_digit_x, NULL)
		|| strany(rgb_arr[1], is_not_digit_x, NULL)
		|| strany(rgb_arr[2], is_not_digit_x, NULL))
		return (str_arr_dispose(rgb_arr), FAILURE);
	rgb[0] = ft_atoi(rgb_arr[0]);
	rgb[1] = ft_atoi(rgb_arr[1]);
	rgb[2] = ft_atoi(rgb_arr[2]);
	str_arr_dispose(rgb_arr);
	if (!rgb_validate(rgb))
		return (FAILURE);
	*color = (rgb[0] << 16) | (rgb[1] << 8) | (rgb[2] << 0);
	return (SUCCESS);
}

size_t	map_meta_key_len(t_meta key)
{
	if (key == META_END)
		return (0);
	else if (key == META_NO || key == META_WE || key == META_EA || key == META_SO)
		return (2);
	return (1);
}

char	**map_split_line(char *data)
{
	char	**lines;

	if (!data)
		return (NULL);
	lines = ft_split(data, '\n');
	return (lines);
}
