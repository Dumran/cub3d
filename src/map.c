#include "cub3d.h"
#include <unistd.h>
#include <fcntl.h>

t_err	set_buf_by_miss_empty_line(int fd, char **buf)
{
	char	*tmp;

	while (true)
	{
		*tmp = get_next_line(fd);
		if (*tmp)
			return (FAILURE);
		buf = ft_strtrim(tmp, " \t\v\f\r\n");
		if (*buf)
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
			return (perr("buf cannot be allocated"));
		err = map_meta_set_value(s, buff);
		if (err)
			return (FAILURE);
		loop--;
	}
	return (SUCCESS);
}

t_err	is_valid_mid(t_state *s, char *val, int fd)
{
	char	*prev;
	t_err	err;
	char	*right_trimmed;

	if (!val)
		return (FAILURE);
	while (true)
	{
		ft_lstadd_back(&s->map.map, ft_lstnew(val));
		prev = val;
		val = get_next_line(fd);
		if (!val || *val == '\n')
		{
			err = is_valid_vertical_edge(prev);
			if (err)
				return (FAILURE);
			break ;
		}
		right_trimmed = ft_strrtrim(val, " \t\v\f\r\n");
		if (!right_trimmed)
			return (free(val), perr("right trimmed error"));
		free(val);
		val = right_trimmed;
		// here
	}
}

t_err	map_load_data(t_state *s, int fd)
{
	t_err	err;
	char	*buff;
	char	*val;

	err = set_buf_by_miss_empty_line(fd, &buff);
	if (err)
		return (perr("buf cannot be allocated"));
	val = ft_strrtrim(buff, " \t\v\f\r\n");
	free(buff);
	if (!val)
		return (perr("buff cannot be trimmed"));
	err = is_valid_vertical_edge(val);
	if (err)
		return (free(val), perr("invalid map near to vertical edge"));
	err = is_valid_mid(val);
	if (err)
		return (free(val), perr("invalid map near to mid"));

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
		return (FAILURE);
	err = map_load_data(s, fd);
	if (err)
		return (FAILURE);
	return (SUCCESS);
}
