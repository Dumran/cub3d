#include "cub3d.h"
#include "libft.h"

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
		err = map_meta_set_value(game, *row, override, meta_count);
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

t_err	map_meta_set_value(t_game *game, size_t row, int override[6], int meta_count)
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
	if (meta_count >= 3)
		err = texture_load(game, meta, game->map.lines[row]);
	else
	{
		if (meta == META_C)
			err = color_load(game, &game->texture.ceiling, game->map.lines[row]);
		else
			err = color_load(game, &game->texture.floor, game->map.lines[row]);
	}
	if (err)
		return (FAILURE);
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
