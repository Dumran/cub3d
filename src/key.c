#include "cub3d.h"

void	key_w(t_game *game)
{
	int	h;
	int	w;

	h = (int) game->player.pos.x + game->player.dir.x * G_SPEED;
	w = (int) game->player.pos.y;
	if (game->map.map[h][w] == '0' || is_character(game->map.map[h][w]))
		game->player.pos.x += game->player.dir.x * G_SPEED;
	h = (int) game->player.pos.x;
	w = (int) game->player.pos.y + game->player.dir.y * G_SPEED;
	if (game->map.map[h][w] == '0' || is_character(game->map.map[h][w]))
		game->player.pos.y += game->player.dir.y * G_SPEED;
}

void	key_a(t_game *game)
{
	int	h;
	int	w;

	h = (int) game->player.pos.x - game->player.dir.y * G_SPEED;
	w = (int) game->player.pos.y;
	if (game->map.map[h][w] == '0' || is_character(game->map.map[h][w]))
		game->player.pos.x -= game->player.dir.y * G_SPEED;
	h = (int) game->player.pos.x;
	w = (int) game->player.pos.y + game->player.dir.x * G_SPEED;
	if (game->map.map[h][w] == '0' || is_character(game->map.map[h][w]))
		game->player.pos.y += game->player.dir.x * G_SPEED;
}

void	key_s(t_game *game)
{
	int	h;
	int	w;

	h = (int) game->player.pos.x - game->player.dir.x * G_SPEED;
	w = (int) game->player.pos.y;
	if (game->map.map[h][w] == '0' || is_character(game->map.map[h][w]))
		game->player.pos.x -= game->player.dir.x * G_SPEED;
	h = (int) game->player.pos.x;
	w = (int) game->player.pos.y - game->player.dir.y * G_SPEED;
	if (game->map.map[h][w] == '0' || is_character(game->map.map[h][w]))
		game->player.pos.y -= game->player.dir.y * G_SPEED;
}

void	key_d(t_game *game)
{
	int	h;
	int	w;

	h = (int) game->player.pos.x + game->player.dir.y * G_SPEED;
	w = (int) game->player.pos.y;
	if (game->map.map[h][w] == '0' || is_character(game->map.map[h][w]))
		game->player.pos.x += game->player.dir.y * G_SPEED;
	h = (int) game->player.pos.x;
	w = (int) game->player.pos.y - game->player.dir.x * G_SPEED;
	if (game->map.map[h][w] == '0' || is_character(game->map.map[h][w]))
		game->player.pos.y -= game->player.dir.x * G_SPEED;
}
