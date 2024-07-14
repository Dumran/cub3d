#include "cub3d.h"

t_err	map_meta_set_value(t_state *s, char *buff)
{
	t_key	key;
	char	*val;
	t_err	err;

	key = map_meta_get_key(buff);
	if (key == KEY_END)
		return (perr("key error has been occurred"));
	if (s->override[key])
		return (perr("duplicate key"));
	s->override[key] = 1;
	if (!ft_isspace(buff[map_meta_key_len(key)]))
		return (perr("no space separator"));
	val = ft_strtrim(buff + map_meta_key_len(key), " \t\v\f\r\n");
	if (!val)
		return (perr("trimmed value cannot be allocated"));
	err = map_meta_invoke(s, key, val);
	if (err)
		return (free(val), FAILURE);
	return (free(val), SUCCESS);
}

t_key	map_meta_get_key(char *buff)
{
	if (!ft_strncmp(STR_NO, buff, 2))
		return (NO);
	if (!ft_strncmp(STR_SO, buff, 2))
		return (SO);
	if (!ft_strncmp(STR_WE, buff, 2))
		return (WE);
	if (!ft_strncmp(STR_EA, buff, 2))
		return (EA);
	if (!ft_strncmp(STR_F, buff, 1))
		return (F);
	if (!ft_strncmp(STR_C, buff, 1))
		return (C);
	return (KEY_END);
}

size_t	map_meta_key_len(t_key key)
{
	if (key == NO || key == SO || key == WE || key == EA)
		return (2);
	if (key == F || key == C)
		return (1);
	return (0);
}

t_err	rgb_set(char *val, unsigned int *color)
{
	char	**rgb;
	int		arr[3];

	rgb = ft_split(val, ',');
	if (!rgb)
		return (FAILURE);
	if (ft_arrlen(rgb) != 3)
		return (ft_arrfree_2d(rgb), FAILURE);
	if (!(ft_strevery(rgb[0], ft_isdigit_x, NULL) &&
		ft_strevery(rgb[1], ft_isdigit_x, NULL) &&
		ft_strevery(rgb[2], ft_isdigit_x, NULL)))
		return (ft_arrfree_2d(rgb), FAILURE);
	arr[0] = ft_atoi(rgb[0]);
	arr[1] = ft_atoi(rgb[1]);
	arr[2] = ft_atoi(rgb[2]);
	ft_arrfree_2d(rgb);
	if (arr[0] > 255 || arr[1] > 255 || arr[2] > 255 ||
		arr[0] < 0 || arr[1] < 0 || arr[2] < 0)
		return (FAILURE);
	return (*color = (arr[0] << 16) | (arr[1] << 8) | arr[2], SUCCESS);
}

t_err	map_meta_set_color(t_state *s, t_key key, char *val)
{
	t_err	err;

	if (key == F)
	{
		err = rgb_set(val, s->floor);
		if (err)
			return (perr("invalid color"));
	}
	else if (key == C)
	{
		err = rgb_set(val, s->ceiling);
		if (err)
			return (perr("invalid color"));
	}
	return (SUCCESS);
}

t_err	map_meta_set_texture(t_state *s, char *path, t_dir idx)
{
	t_list	*approved;

	s->images[idx].img = mlx_xpm_file_to_image(s->mlx, path,
		&s->images[idx].width, &s->images[idx].height);
	if (s->images[idx].img == NULL)
		return (perr("textures cannot be loaded"));
	s->images[idx].addr = (int *)mlx_get_data_addr(s->images[idx].img,
		&s->images[idx].bits_per_pixel, &s->images[idx].size_line,
		&s->images[idx].endian);
	if (s->images[idx].addr == NULL)
		return (perr("textures cannot be loaded"));
	approved = ft_lstnew(s->images[idx].img);
	if (!approved)
		return (FAILURE);
	ft_lstadd_back(&s->approved_textures, approved);
	return (SUCCESS);
}

t_err	map_meta_invoke(t_state *s, t_key key, char *val)
{
	if (map_meta_key_len(key) == 2)
		return (map_meta_set_texture(s, val, (t_dir) key));
	else
		return (map_meta_set_color(s, key, val));
}
