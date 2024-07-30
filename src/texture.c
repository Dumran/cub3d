#include <cub3d.h>
#include <math.h>

void	set_texture_values(t_game *game)
{
	double	wall_x;

	if (game->ray.side == 0)
		wall_x = game->player.pos.y + game->ray.perp_wall_dist * game->ray.dir.y;
	else
		wall_x = game->player.pos.x + game->ray.perp_wall_dist * game->ray.dir.x;
	wall_x -= floor(wall_x);
	game->ray.tex_x = (int)(wall_x * (double)64);
	if (game->ray.side == 0 && game->ray.dir.x > 0)
		game->ray.tex_x = 64 - game->ray.tex_x - 1;
	if (game->ray.side == 1 && game->ray.dir.y < 0)
		game->ray.tex_x = 64 - game->ray.tex_x - 1;
	game->ray.tex_step = 1.0 * 64 / game->ray.line_height;
	game->ray.tex_pos = (game->ray.draw_start - WIN_Y
			/ 2 + game->ray.line_height / 2) * game->ray.tex_step;
}

void	draw_wall_texture(t_game *game, int i, t_img img)
{
	int			tex_y;

	while (game->ray.draw_start < game->ray.draw_end)
	{
		tex_y = (int)game->ray.tex_pos & 63;
		game->ray.tex_pos += game->ray.tex_step;
		if (img.addr[64 * tex_y + game->ray.tex_x] > 0)
			game->mlx_o_game[game->ray.draw_start * WIN_X + i]
				= img.addr[64 * tex_y + game->ray.tex_x];
		game->ray.draw_start++;
	}
}

void	draw_wall_side(t_game *game, int i)
{
	set_texture_values(game);
	if (game->ray.side == 0 && game->ray.dir.x > 0)
		draw_wall_texture(game, i, game->texture.north);
	else if (game->ray.side == 0 && game->ray.dir.x < 0)
		draw_wall_texture(game, i, game->texture.south);
	else if (game->ray.side == 1 && game->ray.dir.y > 0)
		draw_wall_texture(game, i, game->texture.west);
	else
		draw_wall_texture(game, i, game->texture.east);
}