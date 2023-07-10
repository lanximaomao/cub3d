/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:31:11 by asarikha          #+#    #+#             */
/*   Updated: 2023/07/10 14:34:29 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	pixel_color(t_cub *cub3d, int x, int y, int color)
{
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	*dst;

	cub3d->img->addr = mlx_get_data_addr(cub3d->img->img_ptr,
			&bits_per_pixel, &line_length, &endian);
	dst = cub3d->img->addr + (y * line_length + x * (bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static	void	draw_nose(t_cub *cub3d)
{
	t_position	t1;
	t_position	t2;

	t1.x_p = cub3d->var->px;
	t2.x_p = cub3d->var->px + (cub3d->var->pdx * 20);
	t1.y_p = cub3d->var->py;
	t2.y_p = cub3d->var->py + (cub3d->var->pdy * 20);
	bresenham_line (t1, t2, cub3d);
}

void	render(t_cub *cub3d)
{
	mlx_clear_window(cub3d->mlx_ptr, cub3d->win_ptr);
	//drwa_background(cub3d);
	if (cub3d->input->position->x_p != -1)
		return (creat_player(cub3d, cub3d->input->position->x_p
				, cub3d->input->position->y_p, PURPLE));
	draw_map2d(cub3d);
	draw_player2d(cub3d);
	draw_nose(cub3d);
	//calculate_rays(cub3d);
	mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->win_ptr,
		cub3d->img->img_ptr, 0, 0);
}
