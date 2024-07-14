#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>

t_map	*map_init(const char *file)
{
	t_map	*map;

	if (!file)
		return (NULL);
	map = (t_map *) malloc(sizeof(t_map));
	if (!map)
		return (perr("map cannot be allocated"), NULL);
	if (!is_valid_file_ext(file))
		return (free(map), perr("invalid file extention"), NULL);
	map->path = file;
	map->map = NULL;
	map->w = 0;
	map->h = 0;
	map->size = 0;
	return (map);
}

t_ray	*ray_init(void)
{
	t_ray	*ray;

	ray = (t_ray *) malloc(sizeof(t_ray));
	if (!ray)
		return (perr("ray cannot be allocated"), NULL);
	ray->player = (t_vec) {0};
	ray->dir = (t_vec) {0};
	ray->side_dist = (t_vec) {0};
	ray->plane = (t_vec) {0};
	ray->camera_x = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
	ray->tex_x = 0;
	ray->tex_step = 0;
	ray->tex_pos = 0;
	return (ray);
}

t_err	mlx_init_x(t_state *s)
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	if (!mlx)
		return (perr("mlx cannot be initialized"));
	win = mlx_new_window(mlx, APP_W, APP_H, APP_NAME);
	if (!win)
		return (perr("win cannot be initialized"));
	s->win_img.img = mlx_new_image(mlx, APP_W, APP_H);
	if (!s->win_img.img)
		return (mlx_destroy_window(mlx, win), perr("win_img cannot init"));
	s->win_img.addr = mlx_get_data_addr(s->win_img.img,
		s->win_img.bits_per_pixel, s->win_img.size_line, s->win_img.endian);
	if (!s->win_img.addr)
		return (mlx_destroy_image(mlx, s->win_img.img),
			mlx_destroy_window(mlx, win), perr("win_img_data cannot be init"));
	s->win_img.height = 0;
	s->win_img.width = 0;
	return (SUCCESS);
}

t_img	**imgs_init(t_state *s)
{

	if (!s)
		return (NULL);
}

t_state	*state_init(const char **av)
{
	t_state	*s;
	t_err	err;

	if (!av)
		return (NULL);
	s = (t_state *) ft_calloc(sizeof(t_state), 1);
	if (!s)
		return (NULL);
	s->map = map_init(av[1]);
	if (!s->map)
		return (free(s), NULL);
	s->ray = ray_init();
	if (!s->ray)
		return (free(s->map), free(s), NULL);
	err = mlx_init_x(s);
	if (err)
		return (free(s->map), free(s), NULL);
	return (s);
}
