/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:31:11 by asarikha          #+#    #+#             */
/*   Updated: 2023/07/18 16:28:17 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

unsigned long	calculate_hex_color(t_color_rgb *rgb)
{
	return ((rgb->r & 0xff) << 16)
		+ ((rgb->g & 0xff) << 8) + (rgb->b & 0xff);
}

void	draw_sky_floor(t_cub *cub3d, t_position	t1, t_position	t2)
{
	t_position		sky_1;
	t_position		sky_2;
	t_position		floor_1;
	t_position		floor_2;
	unsigned long	color;

	sky_1.x_p = t1.x_p;
	sky_1.x_p = t1.x_p;
	sky_1.y_p = 0;
	sky_1.y_p = t1.y_p;
	color = calculate_hex_color(cub3d->input->color_c);
	bresenham_line (sky_1, sky_2, cub3d, color);
	floor_1.x_p = t1.x_p;
	floor_1.x_p = t1.x_p;
	floor_1.y_p = t2.y_p;
	floor_1.y_p = WIN_SIZE_Y - 1;
	color = calculate_hex_color(cub3d->input->color_f);
	bresenham_line (floor_1, floor_2, cub3d, color);
	return ;
}

void	draw_walls(t_cub *cub3d)
{
	t_position	t1;
	t_position	t2;
	int			i;

	cub3d->var->ca = fix_ang(cub3d->var->pa - cub3d->var->ra);
	cub3d->var->dis_h = cub3d->var->dis_h * cos(deg_to_rad(cub3d->var->ca));
	cub3d->var->line_h = 40000 / (cub3d->var->dis_h);
	if (cub3d->var->line_h > 1200)
		cub3d->var->line_h = 1200;
	cub3d->var->line_off = 600 - (cub3d->var->line_h / 2);
	t1.x_p = (cub3d->var->r) * 2;
	t1.y_p = cub3d->var->line_off;
	t2.x_p = cub3d->var->r * 2;
	t2.y_p = cub3d->var->line_off + cub3d->var->line_h;
	i = -1;
	while (++i < 2)
	{
		if (t1.x_p < GRID_P * cub3d->input->map->size_x
			&& t1.y_p < GRID_P * cub3d->input->map->size_y)
			t1.y_p = GRID_P * cub3d->input->map->size_y;
		bresenham_line (t1, t2, cub3d, YELLOW);
		t1.x_p++;
		t2.x_p++;
	}
	draw_sky_floor(cub3d, t1, t2);
}
