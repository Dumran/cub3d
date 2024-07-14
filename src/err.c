#include "cub3d.h"

int	perr(const char *msg)
{
	printf("Error\n");
	if (msg)
		printf("%s\n", msg);
	return (FAILURE);
}
