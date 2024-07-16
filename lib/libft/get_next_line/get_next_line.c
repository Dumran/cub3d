/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehkekli <mehkekli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:14:46 by mehkekli          #+#    #+#             */
/*   Updated: 2024/07/16 15:04:30 by mehkekli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rest = ft_readbuf(fd, rest);
	if (!rest)
		return (NULL);
	line = ft_getline(rest);
	rest = ft_getrest(rest);
	return (line);
}

char	*ft_readbuf(int fd, char *rest)
{
	char	*buf;
	int		b;

	buf = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (free(rest), NULL);
	b = 1;
	while (!ft_strchr_gnl(rest, '\n') && b)
	{
		b = read(fd, buf, BUFFER_SIZE);
		if (b == -1)
			return (free(rest), free(buf), NULL);
		buf[b] = '\0';
		rest = ft_strjoin_gnl(rest, buf);
		if (!rest)
			return (free(rest), free(buf), NULL);
	}
	free(buf);
	return (rest);
}

char	*ft_getline(char *rest)
{
	char	*line;
	int		i;

	i = 0;
	if (!rest[i])
		return (NULL);
	while (rest[i] && rest[i] != '\n')
		i++;
	line = (char *) malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (rest[i] && rest[i] != '\n')
	{
		line[i] = rest[i];
		i++;
	}
	if (rest[i] == '\n')
	{
		line[i] = rest[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_getrest(char *rest)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	while (rest[i] && rest[i] != '\n')
		i++;
	if (!rest[i])
		return (free(rest), NULL);
	new = (char *) malloc((ft_strlen_gnl(rest + i) + 1) * sizeof(char));
	if (!new)
		return (free(rest), NULL);
	j = 0;
	i++;
	while (rest[i + j])
	{
		new[j] = rest[i + j];
		j++;
	}
	new[j] = '\0';
	free(rest);
	return (new);
}
