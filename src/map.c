#include "cub3d.h"
#include <unistd.h>
#include <fcntl.h>

t_err	set_buf_by_miss_empty_line(int fd, char **buf)
{
	char	*tmp;

	while (true)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			return (FAILURE);
		*buf = ft_strtrim(tmp, " \t\v\f\r\n");
		if (!(*buf))
			return (free(tmp), FAILURE);
		if ((*buf)[0] != '\0')
			return (free(tmp), SUCCESS);
		free(tmp);
		tmp = NULL;
		free(*buf);
		*buf = NULL;
	}
	return (FAILURE);
}

t_err	map_load_meta(t_state *s, int fd)
{
	char	*buff;
	int		loop;
	t_err	err;

	loop = KEY_END;
	while (loop)
	{
		err = set_buf_by_miss_empty_line(fd, &buff);
		if (err)
			return (perr("buf cannot be allocated 1"));
		err = map_meta_set_value(s, buff);
		if (err)
			return (FAILURE);
		loop--;
	}
	return (SUCCESS);
}

int	map_validate_vertical_edge(char *row)
{
	return (ft_strany(row, is_valid_vertical_edge_char, NULL));
}

t_err	map_validate_middle(t_state *s, char *val, int fd)
{
	char	*prev;
	char	*right_trimmed;

	if (!val)
		return (FAILURE);
	while (true)
	{
		ft_lstadd_back(&s->map->map, ft_lstnew(val));
		prev = val;
		val = get_next_line(fd);
		if (!val || *val == '\n')
		{
			if (map_validate_vertical_edge(prev))
				return (FAILURE);
			break ;
		}
		right_trimmed = ft_strrtrim(val, " \t\v\f\r\n");
		if (!right_trimmed)
			return (free(val), perr("right trimmed error"));
		free(val);
		val = right_trimmed;
		if (map_validate_row_mid(s, val, prev))
			return (free(val), FAILURE);
	}
	return (SUCCESS);
}

t_err	map_load_data(t_state *s, int fd)
{
	t_err	err;
	char	*buff;
	char	*val;

	err = set_buf_by_miss_empty_line(fd, &buff);
	if (err)
		return (perr("buf cannot be allocated 2"));
	val = ft_strrtrim(buff, " \t\v\f\r\n");
	free(buff);
	if (!val)
		return (perr("buff cannot be trimmed"));
	err = map_validate_vertical_edge(val);
	if (err)
		return (free(val), perr("invalid map near to vertical edge"));
	err = map_validate_middle(s, val, fd);
	if (err)
		return (free(val), perr("invalid map near to mid"));
	err = set_buf_by_miss_empty_line(fd, &buff);
	if (err)
		return (free(val), perr("buf cannot be allocated 3"));
	return (SUCCESS);
}

t_err	map_load(t_state *s)
{
	int		fd;
	t_err	err;

	fd = open(s->map->path, O_RDONLY);
	if (fd == -1)
		return (FAILURE);
	err = map_load_meta(s, fd);
	if (err)
		return (close(fd), FAILURE);
	err = map_load_data(s, fd);
	if (err)
		return (close(fd), map_clear(s), FAILURE);
	if (s->ray->player.x == 0)
		return (close(fd), map_clear(s), perr("player error"));
	return (SUCCESS);
}
