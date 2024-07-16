#include "cub3d.h"
#include <math.h>

void	on_direction(t_state *s, int const x)
{
	if (s->ray->ray_dir.x < 0)
	{
		s->ray->step.x = -1;
		s->ray->side_dist.x = (s->ray->player.x - s->ray->map_y)
			* s->ray->delta_dist.x;
	}
	else
	{
		s->ray->step.x = 1;
		s->ray->side_dist.x = (s->ray->map_y + 1.0 - s->ray->player.x)
			* s->ray->delta_dist.x;
	}
	if (s->ray->ray_dir.y < 0)
	{
		s->ray->step.y = -1;
		s->ray->side_dist.y = (s->ray->player.y - s->ray->map_x)
			* s->ray->delta_dist.y;
	}
	else
	{
		s->ray->step.y = 1;
		s->ray->side_dist.y = (s->ray->map_x + 1.0 - s->ray->player.y)
			* s->ray->delta_dist.y;
	}
	on_wall_hit(s, x);
}
void	on_wall_hit(t_state *s, int const x)
{
	s->ray->wall = 0;
	while (!s->ray->wall)
	{
		if (s->ray->side_dist.x < s->ray->side_dist.y)
		{
			s->ray->side_dist.x += s->ray->delta_dist.x;
			s->ray->map_y += s->ray->step.x;
			s->ray->side = 0;
		}
		else
		{
			s->ray->side_dist.y += s->ray->delta_dist.y;
			s->ray->map_x += s->ray->step.y;
			s->ray->side = 1;
		}
		if (((char *)ll_nod(s->map->map, s->ray->map_y)->content) \
			[s->ray->map_x] == M_WALL)
			s->ray->wall = 1;
	}
	set_ray_dist(s, x);
}

void	set_ray_dist(t_state *s, int const x)
{
	if (s->ray->side == 0)
		s->ray->prep_wall_dist = s->ray->side_dist.x - s->ray->delta_dist.x;
	else
		s->ray->prep_wall_dist = s->ray->side_dist.y - s->ray->delta_dist.y;
	if (s->ray->prep_wall_dist < 0.001)
		s->ray->prep_wall_dist += 0.001;
	s->ray->line_height = \
		(int)(s->win_img.height / s->ray->prep_wall_dist * 2);
	s->ray->draw_start = \
		-s->ray->line_height / 2 + s->win_img.height / 2;
	if (s->ray->draw_start < 0)
		s->ray->draw_start = 0;
	s->ray->draw_end = \
		s->ray->line_height / 2 + s->win_img.height / 2;
	if (s->ray->draw_end >= s->win_img.height)
		s->ray->draw_end = s->win_img.height - 1;
	draw_wall_side(s, x);
}

void	draw_wall_texture(t_state *s, int const x, int const tex_index)
{
	int			tex_y;

	while (s->ray->draw_start < s->ray->draw_end)
	{
		tex_y = (int)s->ray->tex_pos & (s->resolution - 1);
		s->ray->tex_pos += s->ray->tex_step;
		if (s->images[tex_index].addr[(s->resolution * tex_y) + \
			s->ray->tex_x] > 0)
			s->win_img.addr[(s->ray->draw_start * \
			s->win_img.width) + x] = \
			s->images[tex_index].addr[(s->resolution * tex_y) + \
			s->ray->tex_x];
		s->ray->draw_start++;
	}
}

void	prep_texture(t_state *s)
{
	double	wall_x;

	if (s->ray->side == 0)
		wall_x = \
		s->ray->player.y + s->ray->prep_wall_dist * s->ray->ray_dir.y;
	else
		wall_x = \
		s->ray->player.x + s->ray->prep_wall_dist * s->ray->ray_dir.x;
	wall_x -= floor(wall_x);
	s->ray->tex_x = (int)(wall_x * (double)s->resolution);
	if (s->ray->side == 0 && s->ray->ray_dir.x > 0)
		s->ray->tex_x = s->resolution - s->ray->tex_x - 1;
	if (s->ray->side == 1 && s->ray->ray_dir.y < 0)
		s->ray->tex_x = s->resolution - s->ray->tex_x - 1;
	s->ray->tex_step = 1.0 * s->resolution / s->ray->line_height;
	s->ray->tex_pos = (s->ray->draw_start - s->win_img.height
			/ 2 + s->ray->line_height / 2) * s->ray->tex_step;
}

void	draw_wall_side(t_state *s, int const x)
{
	prep_texture(s);
	if (s->ray->side == 0 && s->ray->ray_dir.x > 0)
		draw_wall_texture(s, x, 2);
	else if (s->ray->side == 0 && s->ray->ray_dir.x < 0)
		draw_wall_texture(s, x, 3);
	else if (s->ray->side == 1 && s->ray->ray_dir.y > 0)
		draw_wall_texture(s, x, 1);
	else
		draw_wall_texture(s, x, 0);
}

void	fill_floor_and_ceiling(t_state *s)
{
	int	i;
	int	n;

	i = -1;
	while (++i < s->win_img.height / 2)
	{
		n = -1;
		while (++n < s->win_img.width)
			s->win_img.addr[i * s->win_img.width + n] = \
			s->floor;
	}
	while (++i < s->win_img.height)
	{
		n = -1;
		while (++n < s->win_img.width)
			s->win_img.addr[i * s->win_img.width + n] = \
			s->ceiling;
	}
}

void	on_ray_casting(t_state *s)
{
	int			x;

	x = 0;
	while (x < s->win_img.width)
	{
		s->ray->camera_x = (double)x / (s->win_img.width - 1);
		s->ray->dir.x = (s->ray->dir.x + (s->ray->plane.x * \
			(s->ray->camera_x - 0.5) * 2));
		s->ray->dir.y = (s->ray->dir.y + (s->ray->plane.y * \
			(s->ray->camera_x - 0.5) * 2));
		s->ray->map_y = (int)s->ray->player.x;
		s->ray->map_x = (int)s->ray->player.y;
		s->ray->delta_dist.x = fabs(1 / s->ray->ray_dir.x);
		s->ray->delta_dist.y = fabs(1 / s->ray->ray_dir.y);
		on_direction(s, x);
		x++;
	}
}