#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

t_err	game_load(t_game *game)
{
	t_err	err;
	size_t	row;

	if (!game || !game->map.data)
		return (perr(ESTR_ASSERT_));
	row = 0;
	game->map.lines = map_split_line(game->map.data);
	if (!game->map.lines)
		return (FAILURE);
	err = map_meta_load(game, &row);
	if (err)
		return (FAILURE);
	return (SUCCESS);
}

char	**map_split_line(char *data)
{
	char	**lines;

	if (!data)
		return (NULL);
	lines = ft_split(data, '\n');
	return (lines);
}

t_err	map_meta_load(t_game *game, size_t *row)
{
	t_err	err;
	int		meta_count;
	int		*override;

	if (!game || !game->map.data)
		return (perr(ESTR_ASSERT_));
	meta_count = 6;
	override = (int [6]){0};
	while (game->map.lines[*row] && meta_count)
	{
		err = map_meta_pass_empty(game, row);
		if (err)
			return (FAILURE);
		err = map_meta_set_value(game, *row, override);
		if (err)
			return (FAILURE);
		meta_count--;
		(*row)++;
	}
	return (SUCCESS);
}

t_err	map_meta_pass_empty(t_game *game, size_t *row)
{
	char	*line;

	if (!game || !game->map.lines)
		return (perr(ESTR_ASSERT_));
	while (game->map.lines[*row])
	{
		line = game->map.lines[*row];
		if (line[0] == '\n' || line[0] == '\0')
			(*row)++;
		else
			return (SUCCESS);
	}
	return (perr("invalid map file data"));
}

size_t	map_meta_key_len(t_meta key)
{
	if (key == META_END)
		return (0);
	else if (key == META_NO || key == META_WE || key == META_EA || key == META_SO)
		return (2);
	return (1);
}

t_err	img_load(t_game *game, t_img *img, char *path)
{
	if (!game || !img || !path)
		return (perr(ESTR_ASSERT_));
	dprintf(2, "[DEBUG]: path: %s\n", path);
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

t_err	texture_load(t_game *game, t_meta key, char *line)
{
	char	*value;
	size_t	len;
	t_err	err;

	if (!game || !line || key == META_END)
		return (perr(ESTR_ASSERT_));
	len = map_meta_key_len(key);
	if (!len)
		return (perr("invalid map meta key len"));
	if (!ft_isspace(line[len]))
		return (perr("invalid map meta format"));
	value = ft_substr(line, len, ft_strlen(line) - len);
	if (!value)
		return (perr("map meta value cannot be allocated"));
	value = ft_strtrim_x(value, W_SPACE_SET);
	if (!value)
		return (perr("map meta value cannot be allocated"));
	err = texture_set_value(game, key, value);
	if (err)
		return (free(value), perr("texture cannot be set"));
	return (free(value), SUCCESS);
}

t_err	map_meta_set_value(t_game *game, size_t row, int override[6])
{
	t_meta	meta;
	t_err	err;

	if (!game || !game->map.lines)
		return (perr(ESTR_ASSERT_));
	meta = map_meta_get_key(game->map.lines[row]);
	if (meta == META_END)
		return (perr("invalid map meta key"));
	if (override[meta] == 1)
		return (perr("duplicate map meta key"));
	override[meta] = 1;
	err = texture_load(game, meta, game->map.lines[row]);
	if (err)
		return (FAILURE);
	dprintf(2, "[DEBUG]: img.nor: %p\n", game->texture.north.img);
	dprintf(2, "[DEBUG]: color: %d\n", game->texture.ceiling);
	return (SUCCESS);
}

t_meta	map_meta_get_key(char *line)
{
	if (!line)
		return (META_END);
	if (!ft_strncmp(line, TEXT_NO, 2))
		return (META_NO);
	else if (!ft_strncmp(line, TEXT_SO, 2))
		return (META_SO);
	else if (!ft_strncmp(line, TEXT_WE, 2))
		return (META_WE);
	else if (!ft_strncmp(line, TEXT_EA, 2))
		return (META_EA);
	else if (!ft_strncmp(line, TEXT_F, 1))
		return (META_F);
	else if (!ft_strncmp(line, TEXT_C, 1))
		return (META_C);
	return (META_END);
}
