/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:31:11 by asarikha          #+#    #+#             */
/*   Updated: 2023/06/29 15:32:06 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static	void	creat_img(t_cub *cub3d, int x, int y)
{
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	*dst;
	int		color;

	cub3d->img->addr = mlx_get_data_addr(cub3d->img->img_ptr,
			&bits_per_pixel, &line_length, &endian);
	dst = cub3d->img->addr + (y * line_length + x * (bits_per_pixel / 8));
	color = calculate_color();
	*(unsigned int *)dst = color;
}

void	render(t_cub *cub3d)
{
	mlx_clear_window(cub3d->mlx_ptr, cub3d->win_ptr);
	drawMap2D(cub3d);
	drawPlayer2D(cub3d);
	drawRays2D(cub3d);
	mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->win_ptr,
		cub3d->img->img_ptr, 0, 0);
}
