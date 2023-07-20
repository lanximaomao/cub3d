
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
}			t_position;

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
	void	*tex_ptr;
	int		*tex_data;
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

//parsing-> validation -> raycasting -> possible features
int		validate(void);
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

#endif
