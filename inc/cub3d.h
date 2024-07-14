#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <stdbool.h>
# include <stdio.h>

# define KEY_ESC 		53
# define KEY_LEFT 		123
# define KEY_RIGHT 		124
# define KEY_W 			13
# define KEY_A 			0
# define KEY_S 			1
# define KEY_D 			2

# define ON_KEYDOWN 	2
# define ON_KEYUP 		3
# define ON_MOUSEDOWN	4
# define ON_MOUSEUP		5
# define ON_MOUSEMOVE	6
# define ON_EXPOSE		12
# define ON_DESTROY		17

# define M_WALL '1'
# define M_FLOOR '0'
# define M_NORTH 'N'
# define M_SOUTH 'S'
# define M_WEST 'W'
# define M_EAST 'E'
# define M_ELEMENTS "10NSWE"

# define STR_NO	"NO"
# define STR_SO	"SO"
# define STR_WE	"WE"
# define STR_EA	"EA"
# define STR_F	"F"
# define STR_C	"C"

# define APP_NAME "/bin/cube3d"
# define APP_W 1920
# define APP_H 1080

typedef enum e_err
{
	SUCCESS = 0,
	FAILURE = -1
}	t_err;

typedef struct s_map
{
	t_list		*map;
	int			w;
	int			h;
	int			size;
	const char	*path;
}	t_map;

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

typedef struct s_ray
{
	t_vec	player;
	t_vec	dir;
	t_vec	side_dist;
	t_vec	plane;
	double	camera_x;
	int		draw_start;
	int		draw_end;
	int		tex_x;
	double	tex_step;
	double	tex_pos;
}	t_ray;

typedef struct s_state
{
	void	*mlx;
	void	*win;
	t_img	win_img;
	t_map	*map;
	t_ray	*ray;
	t_img	*images;
	t_list	*approved_textures;
	int		override[KEY_END];
	int		key_size[KEY_END];
	int		floor;
	int		ceiling;
}	t_state;

typedef enum e_key
{
	NO,
	SO,
	WE,
	EA,
	F,
	C,
	KEY_END
}	t_key;

typedef enum e_dir
{
	IDX_NORTH,
	IDX_SOUTH,
	IDX_WEST,
	IDX_EAST,
	IMAGE_COUNT,
}	t_dir;

// main
bool	is_valid_file_ext(const char *file);

// err
int		perr(const char *msg);

// util
size_t	ft_arrlen(void *arr);
size_t	ft_arrfree_2d(void *arr);
int		ft_isdigit_x(unsigned int idx, char *curr, void *param);
int		ft_strevery(char *s, int (*f)(unsigned int i, char *s,
		void *p), void *pass);

// init
t_map	*map_init(const char *file);
t_ray	*ray_init(void);
t_err	mlx_init_x(t_state *s);
t_state	*state_init(const char **av);

// map meta
t_key	map_meta_get_key(char *buff);
size_t	map_meta_key_len(t_key key);
t_err	map_meta_set_value(t_state *s, char *buff, int *meta_count, bool *loop);
t_err	map_meta_set_color(t_state *s, t_key key, char *val);
t_err	map_meta_invoke(t_state *s, t_key key, char *val);
t_err	map_meta_set_texture(t_state *s, char *path, t_dir idx);
t_err	map_meta_set_color(t_state *s, t_key key, char *val);

#endif
