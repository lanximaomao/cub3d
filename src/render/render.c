#include "cub3D.h"

void	pixel_color(t_cub *cub, int x, int y, unsigned long color)
{
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	*dst;

	cub->img->addr = mlx_get_data_addr(cub->img->img_ptr,
			&bits_per_pixel, &line_length, &endian);
	dst = cub->img->addr + (y * line_length + x * (bits_per_pixel / 8));
	*(unsigned int *)dst = color;
	// printf("dst :%s\n\n",dst);
	// printf("cub->img->addr :%s\n",cub->img->addr);
}

static	void	draw_nose(t_cub *cub)
{
	t_position	t1;
	t_position	t2;

	t1.x_p = cub->var->px;
	t2.x_p = cub->var->px + (cub->var->pdx * 10);
	t1.y_p = cub->var->py;
	t2.y_p = cub->var->py + (cub->var->pdy * 10);
	bresenham_line (t1, t2, cub, PURPLE);
}

void	draw_ray(t_cub *cub)
{
	t_position	t1;
	t_position	t2;

	t1.x_p = cub->var->px;
	t2.x_p = cub->var->rx;
	t1.y_p = cub->var->py;
	t2.y_p = cub->var->ry;
	bresenham_line (t1, t2, cub, RED);
}

void	draw_background(t_cub *cub)
{
	int		x;
	int		y;

	y = -1;
	while (++y < WIN_SIZE_Y)
	{
		x = -1;
		while (++x < WIN_SIZE_X)
		{
			pixel_color(cub, x, y, ROYAL_BLUE);
		}
	}
}

void	render(t_cub *cub)
{
	mlx_clear_window(cub->mlx_ptr, cub->win_ptr);
	draw_background(cub);
	draw_map2d(cub);
	draw_player2d(cub);
	draw_nose(cub);
	calculate_rays(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr,
		cub->img->img_ptr, 0, 0);
}
