#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h>
# include <stdio.h>

# define KEY_ESC		53
# define KEY_Q			12
# define KEY_W			13
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2
# define KEY_LEFT		123
# define KEY_RIGHT		124
# define ON_QUIT_TAP	17

# define IDX_KEY_W		0
# define IDX_KEY_A		1
# define IDX_KEY_S		2
# define IDX_KEY_D		3
# define IDX_KEY_LEFT	4
# define IDX_KEY_RIGHT	5

# define WIN_X			1920
# define WIN_Y			1080
# define WIN_T			"/cub3d"
# define G_ROTATE_S		0.05
# define G_SPEED		0.15
# define FILE_EXT_MAP	".cub"
# define FILE_EXT_TEX	".xpm"

# define TEXT_NO		"NO"
# define TEXT_SO		"SO"
# define TEXT_WE		"WE"
# define TEXT_EA		"EA"
# define TEXT_F			"F"
# define TEXT_C			"C"

# define M_NORTH		'N'
# define M_SOUTH		'S'
# define M_WEST			'W'
# define M_EAST			'E'
# define M_WALL			'1'
# define M_FLOOR		'0'

# define W_SPACE_SET	" \t\v\f\r\n"
# define W_INNER_SET	"0NSWE"
# define W_PLAYER_SET	"NSWE"
# define W_MAP_SET		"10NSWE \t\v\f\r\n"

# define ESTR_ASSERT_	"unexpected error"

typedef enum e_err
{
	SUCCESS = 0,
	FAILURE = -1
}	t_err;

typedef enum e_meta
{
	META_NO,
	META_SO,
	META_WE,
	META_EA,
	META_F,
	META_C,
	META_END,
}	t_meta;

typedef union u_vec
{
	struct
	{
		double	x;
		double	y;
	};
	struct
	{
		int		ax;
		int		ay;
	};
}	t_vec;

typedef struct s_img
{
	void		*img;
	int			*addr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int			width;
	int			height;
}	t_img;

typedef struct s_player
{
	t_vec		pos;
	t_vec		dir;
	int			keys[6];
}	t_player;

typedef struct s_ray
{
	int			wall;
	int			side;
	int			tex_x;
	t_vec		plane;
	t_vec		dir;
	t_vec		a_step;
	t_vec		a_map;
	t_vec		s_dist;
	t_vec		d_dist;
	double		camera_x;
	double		perp_wall_dist;
	double		tex_step;
	double		tex_pos;
	int			line_height;
	int			draw_start;
	int			draw_end;
}	t_ray;

typedef struct s_map
{
	char		*data;
	char		**lines;
	char		**map;
}	t_map;

typedef struct s_texture
{
	t_img	north;
	t_img	west;
	t_img	east;
	t_img	south;
	int		ceiling;
	int		floor;
}	t_texture;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		scr_img;
	t_map		map;
	t_player	player;
	t_ray		ray;
	t_texture	texture;
}	t_game;

// dispose
void		game_dispose(t_game *game);
void		texture_dispose(t_game *game);
void		map_dispose(t_map *map);
void		str_arr_dispose(char **arr);

// err
t_err		perr(const char *msg);

// file
bool		file_ext_validate(const char *path, const char *ext);

// game
t_err		game_init(t_game *game, const char *path);
t_err		game_load(t_game *game);
t_err		game_loop(t_game *game);


// hook
int			on_game_quit(t_game *game);
int			on_loop(void *param);
int			on_move(t_game *game);
int			on_key_press(const int keycode, t_game *game);
int			on_key_release(const int keycode, t_game *game);

// init
t_err		mlx_init_x(t_game *game);
t_err		map_init(t_game *game, const char *path);
t_err		scr_img_init(t_game *game);
t_err		mlx_hook_init_x(t_game *game);

// key util
void		key_left(t_game *game);
void		key_right(t_game *game);

// key
void		key_w(t_game *game);
void		key_a(t_game *game);
void		key_s(t_game *game);
void		key_d(t_game *game);

// map meta
t_err		map_meta_load(t_game *game, size_t *row);
t_err		map_meta_pass_empty(t_game *game, size_t *row);
t_err		map_meta_set_value(t_game *game, size_t row, int override[6], int meta_count);
t_meta		map_meta_get_key(char *line);
t_err		texture_load(t_game *game, t_meta key, char *line);

// map meta util
t_err		texture_set_value(t_game *game, t_meta key, char *value);
t_err		img_load(t_game *game, t_img *img, char *path);
t_err		color_load(t_game *game, int *color, char *rgb_str);
size_t		map_meta_key_len(t_meta key);
char		**map_split_line(char *data);

// map data
t_err		map_data_load(t_game *game, size_t *row);
t_err		map_data_validate(t_game *game);
char		**map_data_create_test_map(t_game *game, size_t w, size_t h);
t_err		map_data_copy_map(t_game *game, size_t w, size_t h, char **test_map);
t_err		map_data_validate_test_map(char **test_map, size_t w, size_t h);

// map data util
bool		map_data_validate_char(t_game *game);
int			map_data_count_player(t_game *game);

// render
void		fill_floor_and_ceiling(t_game *game);
void		ray_casting(t_game *game);
void		send_ray(t_game *game, int i);
void		set_direction(t_game *game);
void		set_wall_hit(t_game *game);
void		set_ray_dist(t_game *game);

// texture
void		set_texture_values(t_game *game);
void		draw_wall_texture(t_game *game, int i, t_img *img);
void		draw_wall_side(t_game *game, int i);

// util str
size_t		str_arr_len(char **arr);
bool		ft_isspace(const int c);
char		*ft_strtrim_x(const char *str, const char *set);
int			strany(char *s, int (*f)(unsigned int idx, char *str, void *p), void *pass);
bool		str_include(const char *str, const char c);

// util
int			is_not_digit_x(unsigned int idx, char *curr, void *param);
int			is_not_x_or_one(unsigned int idx, char *curr, void *param);
bool		rgb_validate(int rgb[3]);
int			is_not_x_or_one_vertical(unsigned int idx, char *curr, void *param);
bool		is_character(const char c);

#endif