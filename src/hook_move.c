#include "cub3d.h"
#include <math.h>

bool	is_character(char const c)
{
	if (c == M_NORTH || c == M_SOUTH
		|| c == M_EAST || c == M_WEST)
		return (true);
	return (false);
}

void	key_w(t_state *s)
{
	char	*map_line;
	int		py;

	map_line = (char *) ll_nod(s->map->map, (int) (s->ray->player.x + s->ray->dir.x * MOVEMENT_SPEED))->content;
	py = (int) (s->ray->player.y);
	if (map_line[py] == M_FLOOR || is_character(map_line[py]))
		s->ray->player.x += s->ray->dir.x * MOVEMENT_SPEED;
	map_line = (char *) ll_nod(s->map->map, (int) s->ray->player.x)->content;
	py = (int) (s->ray->player.y + s->ray->dir.y * MOVEMENT_SPEED);
	if (map_line[py] == M_FLOOR || is_character(map_line[py]))
		s->ray->player.y += s->ray->dir.y * MOVEMENT_SPEED;
}


void	key_s(t_state *s)
{
	if (((char *)ll_nod(s->map->map, (int)(s->ray->player.x - s->ray->dir.x * MOVEMENT_SPEED))->content)[(int)(s->ray->player.y)] == M_FLOOR || \
		is_character(((char *)ll_nod(s->map->map, (int)(s->ray->player.x - \
		s->ray->dir.x * MOVEMENT_SPEED)))[(int)(s->ray->player.y)]))
		s->ray->player.x -= s->ray->dir.x * MOVEMENT_SPEED;
	if (((char *)ll_nod(s->map->map, (int)s->ray->player.x)->content)[(int)(\
		s->ray->player.y - s->ray->dir.y * MOVEMENT_SPEED)] == M_FLOOR || \
		is_character(((char *)ll_nod(s->map->map, (int)s->ray->player.x))[(\
		int)(s->ray->player.y - s->ray->dir.y * MOVEMENT_SPEED)]))
		s->ray->player.y -= s->ray->dir.y * MOVEMENT_SPEED;
}

void	key_a(t_state *s)
{
	if (((char *)ll_nod(s->map->map, (int)(s->ray->player.x - s->ray->dir.y * MOVEMENT_SPEED))->content)[(int)(s->ray->player.y)] == M_FLOOR || \
		is_character(((char *)ll_nod(s->map->map, (int)(s->ray->player.x - \
		s->ray->dir.y * MOVEMENT_SPEED))->content)[(int)(s->ray->player.y)]))
		s->ray->player.x -= s->ray->dir.y * MOVEMENT_SPEED;
	if (((char *)ll_nod(s->map->map, (int)s->ray->player.x)->content)[(int)(\
		s->ray->player.y + s->ray->dir.x * MOVEMENT_SPEED)] == M_FLOOR || \
		is_character(((char *)ll_nod(s->map->map, (int)s->ray->player.x)->\
		content)[(int)(s->ray->player.y + s->ray->dir.x * \
		MOVEMENT_SPEED)]))
		s->ray->player.y += s->ray->dir.x * MOVEMENT_SPEED;
}

void	key_d(t_state *s)
{
	if (((char *)ll_nod(s->map->map, (int)(s->ray->player.x + s->ray->dir.y * MOVEMENT_SPEED))->content)[(int)(s->ray->player.y)] == M_FLOOR || \
		is_character(((char *)ll_nod(s->map->map, (int)(s->ray->player.x + \
		s->ray->dir.y * MOVEMENT_SPEED))->content)[(int)(s->ray->player.y)]))
		s->ray->player.x += s->ray->dir.y * MOVEMENT_SPEED;
	if (((char *)ll_nod(s->map->map, (int)s->ray->player.x)->content)[(int)(\
		s->ray->player.y - s->ray->dir.x * MOVEMENT_SPEED)] == M_FLOOR || \
		is_character(((char *)ll_nod(s->map->map, (int)s->ray->player.x)->\
		content)[(int)(s->ray->player.y - s->ray->dir.x * \
		MOVEMENT_SPEED)]))
		s->ray->player.y -= s->ray->dir.x * MOVEMENT_SPEED;
}

void	key_right(t_state *s)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = s->ray->dir.x;
	s->ray->dir.x = s->ray->dir.x * cos(-ROTATION_SPEED) - \
		s->ray->dir.y * sin(-ROTATION_SPEED);
	s->ray->dir.y = old_dir_x * sin(-ROTATION_SPEED) + s->ray->dir.y
		* cos(-ROTATION_SPEED);
	old_plane_x = s->ray->plane.x;
	s->ray->plane.x = s->ray->plane.x * cos(-ROTATION_SPEED) - \
		s->ray->plane.y * sin(-ROTATION_SPEED);
	s->ray->plane.y = old_plane_x * sin(-ROTATION_SPEED) + \
		s->ray->plane.y * cos(-ROTATION_SPEED);
}

void	key_left(t_state *s)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = s->ray->dir.x;
	s->ray->dir.x = s->ray->dir.x * cos(ROTATION_SPEED) - \
		s->ray->dir.y * sin(ROTATION_SPEED);
	s->ray->dir.y = old_dir_x * sin(ROTATION_SPEED) + s->ray->dir.y
		* cos(ROTATION_SPEED);
	old_plane_x = s->ray->plane.x;
	s->ray->plane.x = s->ray->plane.x * cos(ROTATION_SPEED) - \
		s->ray->plane.y * sin(ROTATION_SPEED);
	s->ray->plane.y = old_plane_x * sin(ROTATION_SPEED) + s->ray->plane.y
		* cos(ROTATION_SPEED);
}
