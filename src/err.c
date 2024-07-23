#include "cub3d.h"
#include <stdio.h>

t_err	perr(const char *msg)
{
	write(2, "Error\n", 6);
	if (msg)
	{
		write(2, "Message: ", 9);
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
	}
	return (FAILURE);
}
