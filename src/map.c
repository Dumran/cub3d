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
			return (SUCCESS);
		free(tmp);
		tmp = NULL;
		free(*buf);
		*buf = NULL;
	}
	return (FAILURE);
}

t_err	map_load_meta(int fd)
{
	char	*buf;
	bool	loop;
	t_err	err;

	while (loop)
	{
		err = set_buf_by_miss_empty_line(fd, &buf);
		if (err)
			return (perr("buf cannot be allocated"));
		

	}
}

t_err	map_load(t_state *s)
{
	int		fd;

	fd = open(s->map->path, O_RDONLY);
	if (fd == -1)
		return (FAILURE);

}
