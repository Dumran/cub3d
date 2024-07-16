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
# define KEY_Q 			12

# define ON_KEYDOWN 	2
# define ON_KEYUP 		3
# define ON_MOUSEDOWN	4
# define ON_MOUSEUP		5
# define ON_MOUSEMOVE	6
# define ON_EXPOSE		12
# define ON_DESTROY		17

# define FOV 			0.44

# define DEG_E			0
# define DEG_N			90
# define DEG_W			180
# define DEG_S			270

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

# define ROTATION_SPEED			0.05
# define MOVEMENT_SPEED			0.1

# define KEY_IDX_W				0
# define KEY_IDX_A				1
# define KEY_IDX_S				2
# define KEY_IDX_D				3
# define KEY_IDX_LARROW			4
# define KEY_IDX_RARROW			5

typedef enum e_err
{
	SUCCESS = 0,
	FAILURE = -1
}	t_err;

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

typedef enum e_char_type
{
	CHR_NONE,
	CHR_INVALID,
	CHR_SPACE,
	CHR_FRAME,
	CHR_SURROUNDABLE
}	t_char_type;

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
	int		player_dir_degree;
	t_vec	dir;
	t_vec	side_dist;
	t_vec	plane;
	t_vec	delta_dist;
	t_vec	ray_dir;
	double	camera_x;
	double	prep_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_x;
	int		wall;
	int		side;
	t_vec	step;
	double	tex_step;
	double	tex_pos;
	int		map_x;
	int		map_y;
}	t_ray;

typedef struct s_state
{
	void	*mlx;
	void	*win;
	t_img	win_img;
	t_map	*map;
	t_ray	*ray;
	t_img	images[IMAGE_COUNT];
	t_list	*approved_textures;
	int		override[KEY_END];
	int		key_size[KEY_END];
	int		floor;
	int		ceiling;
	int		player_keys[KEY_END];
	int		resolution;
}	t_state;

// main
bool	is_valid_file_ext(const char *file);

// err
int		perr(const char *msg);

// util
size_t	ft_arrlen(void *arr);
void	ft_arr_free_2d(void *arr);
int		ft_isdigit_x(unsigned int idx, char *curr, void *param);
int		ft_strevery(char *s, int (*f)(unsigned int i, char *s,
		void *p), void *pass);
int		is_valid_vertical_edge_char(unsigned int idx, char *c, void *p);
bool	is_valid_edge_char(const char *const row);
int		is_able_to_be_surrounded(unsigned int idx, char *c, void *p);
double	deg_to_rad(double degree);
void	map_clear(t_state *s);
void	pass(void *content);
void	textures_dispose(t_state *s);
t_list	*ll_nod(t_list const *node, int index);
int		ft_isspace(int const c);

// init
t_map	*map_init(const char *file);
t_ray	*ray_init(void);
t_err	mlx_init_x(t_state *s);
t_state	*state_init(const char **av);
char	*ft_strrtrim(const char *s1, const char *set);
int		ft_strany(char *s, int (*f)(unsigned int idx, char *str, void *ptr), void *pass);

// map
t_err	set_buf_by_miss_empty_line(int fd, char **buf);
t_err	map_load_meta(t_state *s, int fd);
t_err	map_load_data(t_state *s, int fd);
t_err	map_load(t_state *s);
t_err	map_validate_middle(t_state *s, char *val, int fd);

// map validate
t_err	map_validate_row_mid(t_state *s, char *row, char *prev);
t_err	map_validate_surroundings(char *row, char *prev, size_t prev_len, size_t i);
t_char_type	char_type_get(char const c);

// map meta
t_key	map_meta_get_key(char *buff);
size_t	map_meta_key_len(t_key key);
t_err	map_meta_set_value(t_state *s, char *buff);
t_err	map_meta_set_color(t_state *s, t_key key, char *val);
t_err	map_meta_invoke(t_state *s, t_key key, char *val);
t_err	map_meta_set_texture(t_state *s, char *path, t_dir idx);
t_err	map_meta_set_color(t_state *s, t_key key, char *val);
t_err	rgb_set(char *val, int *color);

// hook move
bool	is_character(char const c);
void	key_w(t_state *s);
void	key_s(t_state *s);
void	key_a(t_state *s);
void	key_d(t_state *s);
void	key_right(t_state *s);
void	key_left(t_state *s);

// hook
int		on_quit_game(t_state *s);
int		on_key_press(int keycode, t_state *s);
int		on_key_release(int keycode, t_state *s);
void	on_move(t_state *s);
void	hook_init(t_state *s);

// render
void	fill_floor_and_ceiling(t_state *s);
void	on_ray_casting(t_state *s);
void	on_direction(t_state *s, int const x);
void	on_wall_hit(t_state *s, int const x);
void	set_ray_dist(t_state *s, int const x);
void	prep_texture(t_state *s);
void	draw_wall_texture(t_state *s, int const x, int const tex_index);
void	draw_wall_side(t_state *s, int const x);

#endif
