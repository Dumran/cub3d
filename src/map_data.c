#include "cub3d.h"
#include "libft.h"
#include <stdlib.h>

t_err	map_data_load(t_game *game, size_t *row)
{
	t_err	err;
	size_t	i;
	size_t	counter;

	if (!game || !game->map.lines)
		return (perr(ESTR_ASSERT_));
	err = map_meta_pass_empty(game, row);
	if (err)
		return (FAILURE);
	i = *row;
	counter = 0;
	while (game->map.lines[i++])
		counter++;
	game->map.map = (char **) malloc(sizeof(char *) * (counter + 1));
	if (!game->map.map)
		return (perr("map cannot be allocated"));
	i = 0;
	while (game->map.lines[*row])
	{
		game->map.map[i] = game->map.lines[*row];
		(*row)++;
		i++;
	}
	game->map.map[i] = NULL;
	return (SUCCESS);
}

t_err	map_data_validate(t_game *game)
{
	char	**test_map;
	size_t	width;
	size_t	height;
	size_t	i;

	if (!game || !game->map.map)
		return (perr(ESTR_ASSERT_));
	i = 0;
	width = 0;
	height = 0;
	while (game->map.map[i])
	{
		if (ft_strlen(game->map.map[i]) > width)
			width = ft_strlen(game->map.map[i]);
		height++;
		i++;
	}
	if (!map_data_validate_char(game))
		return (perr("invalid map character"));
	if (map_data_count_player(game) != 1)
		return (perr("invalid player count"));
	test_map = map_data_create_test_map(game, width, height);
	if (!test_map)
		return (perr("test map cannot be created"));
	return (map_data_validate_test_map(test_map, width, height));
}

char	**map_data_create_test_map(t_game *game, size_t w, size_t h)
{
	char	**test_map;
	size_t	i;

	if (!game || !game->map.map || !w || !h)
		return (NULL);
	test_map = (char **) malloc(sizeof(char *) * (h + 1));
	if (!test_map)
		return (NULL);
	i = 0;
	while (game->map.map[i])
	{
		test_map[i] = (char *) malloc(sizeof(char) * (w + 1));
		if (!test_map[i])
			return (str_arr_dispose(test_map), NULL);
		i++;
	}
	if (map_data_copy_map(game, w, h, test_map))
		return ((str_arr_dispose(test_map), NULL));
	i = 0;
	for (int i = 0; test_map[i]; i++)
		dprintf(2, "[DEBUG]: %s\n", test_map[i]);
	return (test_map);
}

t_err	map_data_copy_map(t_game *game, size_t w, size_t h, char **test_map)
{
	size_t 	i;
	size_t 	j;
	bool	endl;

	if (!game || !game->map.map || !w || !h || !test_map)
		return (perr(ESTR_ASSERT_));
	i = 0;
	endl = false;
	while (i < h)
	{
		j = 0;
		while (j < w && game->map.map[i])
		{
			if (!endl && !game->map.map[i][j])
				endl = true;
			if (!endl && !ft_isspace(game->map.map[i][j]))
				test_map[i][j] = game->map.map[i][j];
			else
				test_map[i][j] = 'X';
			j++;
		}
		endl = false;
		test_map[i++][j] = '\0';
	}
	return (test_map[i] = NULL, SUCCESS);
}


t_err	map_data_validate_test_map(char **test_map, size_t w, size_t h)
{
	size_t i;
	size_t j;

	if (!test_map)
		return (perr(ESTR_ASSERT_));
	i = 0;
	if (strany(test_map[i], is_not_x_or_one, NULL) ||
		strany(test_map[h - 1], is_not_x_or_one, NULL))
		return (perr("invalid map border (horizontal)"));
	while (test_map[i])
		if (strany(test_map[i++], is_not_x_or_one_vertical, NULL))
			return (perr("invalid map border (vertical)"));
	i = 1;
	while (i < h - 1)
	{
		j = 1;
		while (j < w - 1)
		{
			if (test_map[i][j] == 'X' &&
				(str_include(W_INNER_SET, test_map[i - 1][j]) ||
				str_include(W_INNER_SET, test_map[i + 1][j]) ||
				str_include(W_INNER_SET, test_map[i][j - 1]) ||
				str_include(W_INNER_SET, test_map[i][j + 1])))
				return (perr("invalid map unclosed"));
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
