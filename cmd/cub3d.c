#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game	*game;
	t_err	err;
	(void)av;

	if (ac != 2)
		return (perr(ESTR_INV_ARG));
	game = &(t_game){0};
	err = game_init(game, av[1]);
	if (err)
		return (FAILURE);
	dprintf(2, "[DEBUG]: str: %s\n", game->map.data);
	// err = game_load(game);
	// if (err)
	// 	return (FAILURE);
	// err = game_loop(game);
	// if (err)
	// 	return (FAILURE);
	return (FAILURE);
}
