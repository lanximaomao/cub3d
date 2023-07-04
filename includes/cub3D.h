/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:31:11 by asarikha          #+#    #+#             */
/*   Updated: 2023/07/04 16:22:50 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <fcntl.h>
# include <mlx.h>
# include <stdlib.h>
# include "libft.h"
# include "render.h"
# include "event.h"

# ifndef WIN_SIZE_X
#  define WIN_SIZE_X 1920
# endif

# ifndef WIN_SIZE_Y
#  define WIN_SIZE_Y 1080
# endif

typedef struct s_map
{
	char	*map_1d;
	char	**matrix;
	int		size_x;
	int		size_y;
	int		direction;
}			t_map;

typedef struct s_position
{
	int	x_p;
	int	y_p;
}			t_position;

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
	int		px;
	int		py;
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
}			t_vars;


typedef struct s_input
{
	int			*color_f;
	int			*color_c;
	char		*t_east;
	char		*t_west;
	char		*t_south;
	char		*t_north;
	t_map		*map;
	t_position	*position;
}			t_input;


typedef struct s_img
{
	void	*img_ptr;
	int		*addr;
}			t_img;

typedef struct s_cub
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_input	*input;
	t_img	*img;
	t_vars	*var;
}			t_cub;

//parsing-> validation -> raycasting -> possible features
int		validate(void);
void	render(t_cub *cub3d);
int		end_cub3d(t_cub *cub3d);
int		mouse_event(int keycode, int x, int y, t_cub *cub3d);
int		key_event(int keycode, t_cub *cub3d);

#endif
