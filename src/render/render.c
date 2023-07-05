/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:31:11 by asarikha          #+#    #+#             */
/*   Updated: 2023/07/05 15:41:39 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	creat_img(t_cub *cub3d, int x, int y, int color)
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

void	render(t_cub *cub3d)
{
	printf("in render\n");
	mlx_clear_window(cub3d->mlx_ptr, cub3d->win_ptr);
	//drwa_background(cub3d);
	draw_map2d(cub3d);
	draw_player2d(cub3d);
	calculate_rays(cub3d);
	mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->win_ptr,
		cub3d->img->img_ptr, 0, 0);
}
