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
# define G_SENSITIVITY	0.05
# define G_SPEED		0.1
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
	t_vec		plane;
}	t_ray;

typedef struct s_map
{
	char		*data;
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

// err
t_err		perr(const char *msg);

// init
t_err		game_init(t_game *game, const char *path);
t_err		mlx_init_x(t_game *game);
t_err		map_init(t_game *game, const char *path);
t_err		scr_img_init(t_game *game);

// file
bool		file_ext_validate(const char *path, const char *ext);

#endif