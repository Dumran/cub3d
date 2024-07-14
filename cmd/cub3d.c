#include "cub3d.h"
#include <stdlib.h>


bool	is_valid_file_ext(const char *file)
{
	int	i;

	i = 0;
	if(ft_strlen(file) < 4)
		return (false);
	while (file[i])
		i++;
	if (file[i - 1] != 'b' || file[i - 2] != 'u' || file[i - 3] != 'c' ||
		file[i - 4] != '.')
		return (false);
	return (true);
}

int	main(int ac, const char **av)
{
	t_state	*state;

	if (ac != 2)
		return (perr("invalid argument count"));
	state = state_init(av);
	if (!state)
		return (1);
}
