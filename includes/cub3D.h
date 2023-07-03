#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <mlx.h>
# include <stdlib.h>
# include "libft.h"

# ifndef WIN_SIZE_X
# define WIN_SIZE_X 1920
# endif

# ifndef WIN_SIZE_y
# define WIN_SIZE_y 1080
# endif


typedef struct s_map
{
	char	*map_1d;
	char	**matrix;
	int		size_x;
	int		size_y;
	int		direction;
}			t_map;

typedef struct s_input
{
	int		count;
	int		*color_f;
	int		*color_c;
	char	*t_east;
	char	*t_west;
	char	*t_south;
	char	*t_north;
	t_map	*map;
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
}			t_cub;

//parsing-> validation -> raycasting -> possible features
int	validate(void);

#endif
