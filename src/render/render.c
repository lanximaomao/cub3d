/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/07/31 15:18:18 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	pixel_color(t_cub *cub, int x, int y, unsigned long color)
{
	char	*dst;

	cub->img->addr = mlx_get_data_addr(cub->img->img_ptr,
			&cub->img->bpp, &cub->img->line_length,
			&cub->img->endian);
	dst = cub->img->addr + (y * cub->img->line_length + x * (cub->img->bpp
				/ 8));
	if ((x >= 0 && x < WIN_SIZE_X) && (y >= 0 && y < WIN_SIZE_Y))
		*(unsigned int *)dst = color;
}

static void	draw_nose(t_cub *cub)
{
	t_position	t1;
	t_position	t2;

	t1.x_p = cub->var->px;
	t2.x_p = cub->var->px + (cub->var->pdx * 10);
	t1.y_p = cub->var->py;
	t2.y_p = cub->var->py + (cub->var->pdy * 10);
	bresenham_line(t1, t2, cub, PURPLE);
}

void	draw_ray(t_cub *cub)
{
	t_position	t1;
	t_position	t2;

	t1.x_p = cub->var->px;
	t2.x_p = cub->var->rx;
	t1.y_p = cub->var->py;
	t2.y_p = cub->var->ry;
	bresenham_line(t1, t2, cub, RED);
}

void	draw_background(t_cub *cub)
{
	int	x;
	int	y;

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
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img->img_ptr, 0,
		0);
}
