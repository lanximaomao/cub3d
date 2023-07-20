
#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft.h"
# include "render.h"
# include "event.h"
# include "color.h"

# ifndef WIN_SIZE_X
#  define WIN_SIZE_X 1950
# endif

# ifndef WIN_SIZE_Y
#  define WIN_SIZE_Y 1300
# endif

# define ERROR 0
# define SUCCESS 1

// direction 90: North, 270: South, 180: West, 0: East
typedef struct s_map
{
	char	*map_1d;
	char	**matrix;
	int		size_x;
	int		size_y;
	float	direction;
}			t_map;

typedef struct s_position
{
	int	x_p;
	int	y_p;
}		t_position;

typedef struct s_line
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;
}			t_line;

typedef struct s_vars
{
	int		dof;
	float	vx;
	float	vy;
	float	dis_v;
	float	dis_h;
	float	ra;
	float	tan;
	float	rx;
	float	ry;
	float	xo;
	float	yo;
	int		mx;
	int		mp;
	int		my;
	int		r;
	float	px;
	float	py;
	float	pdx;
	float	pdy;
	float	pa;
	int		ca;
	float	line_h;
	float	line_off;
}			t_vars;

typedef struct s_color_rgb
{
	int r;
	int g;
	int b;
} 	t_color_rgb;

typedef struct s_input
{
	int			count;
	//int			*color_f;
	//int			*color_c;
	t_color_rgb	*color_f;
	t_color_rgb	*color_c;
	char		*t_east;
	char		*t_west;
	char		*t_south;
	char		*t_north;
	t_map		*map;
	t_position	*position;
}			t_input;

typedef struct keys
{
	int	w;
	int	a;
	int	d;
	int	s;
	int	left;
	int	right;
	int	up;
	int	down;
	int	xo;
	int	yo;
	int	ipx;
	int	ipy;
	int	ipx_add_xo;
	int	ipy_sub_yo;
	int	ipy_add_yo;
	int	ipx_sub_xo;
	int	ca;
	int	line_h;
	int	line_off;
}		t_keys;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
}			t_img;

typedef struct s_tex
{
	t_img	*img;
	int		size_line;
	int		bpp;
	int		endian;
	int		width;
	int		height;
	char	*type;
}		t_tex;


typedef struct s_cub
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_input	*input;
	t_img	*img;
	t_vars	*var;
	t_keys	*key;
	t_tex	*tex_s;
	t_tex	*tex_e;
	t_tex	*tex_w;
	t_tex	*tex_n;
}			t_cub;


typedef void (*FunctionPointer)(t_cub*);

//parsing-> validation -> raycasting -> possible features
void	render(t_cub *cub3d);
int		end_cub3d(t_cub *cub3d);
int		key_event(int keycode, t_cub *cub3d);
void	draw_map2d(t_cub *cub3d);
void	draw_player2d(t_cub *cub3d);
void	calculate_rays(t_cub *cub3d);
void	pixel_color(t_cub *cub3d, int x, int y, unsigned long color);
void	clean_exit(int exit_code, t_cub *cub3d);
int		message(char *str1, char *str2, int errno);
float	deg_to_rad(float a);
float	fix_ang(float a);
int		bresenham_line(t_position pos0, t_position pos1, t_cub *cub, int color);
void	draw_ray(t_cub *cub3d);
void	draw_walls(t_cub *cub3d);
int		key_press(int keycode, t_cub *cub3d);
int		key_release(int keycode, t_cub *cub3d);
void	init_tex(t_cub *cub3d);

// line
int		bresenham_line(t_position pos0, t_position pos1, t_cub *cub, int color);

// parser.c
int parser(int fd, t_cub *cub);


// init.c
void init_cub(t_cub *cub);
void init_input(t_input *input);
void init_map(t_map *map);

// display.c
void	display_map(char* msg, char **matrix);
void	display_texture(t_input *input);
void	display_color(t_input *input);

// utils
int	free_str(char *str);
int	free_char(char **input);
int free_parsing(t_cub *cub);
void	ft_exit(char* msg, int exit_code);
void	display_color(t_input *input);
int		ft_atoi_isnum(const char *str);
int		how_many(char* str, char c);
int		valid_filetype(char *str);
int		array_size(char **str);
int		loop(t_cub *cub, FunctionPointer member);

// get color
int get_color(t_cub *cub, char* line, int flag);

// get map
int get_matrix(t_cub *cub);
int matrix_revert(t_cub *cub);
int get_map(t_cub *cub, char* line, int *nl_flag);

// get texture
int	get_texture(t_cub *cub, char *line, int flag);

// get_direction
int get_direction(t_cub *cub, int *i, int *j);

// validator
int valid_map(t_cub *cub);
int valid_char(char* str);
int	is_closed(t_cub *cub, int row, int col);
int is_legal_boundary (t_cub *cub, char c, char direction);
int find_char (t_cub *cub, int *row, int *col, char c);
void flood_fill(t_cub *cub, int row, int col, char old);
int find_island(t_cub *cub, int *i, int *j, int *flag);
int is_inland(t_cub *cub, int row, int col, char c);
int valid_filetype(char *str);
char which_dir(t_cub *cub);
int	find_zero(t_cub *cub, int *row, int *col, char c);

#endif
