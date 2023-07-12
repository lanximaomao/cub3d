/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:31:11 by asarikha          #+#    #+#             */
/*   Updated: 2023/07/12 15:54:20 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_walls(t_cub *cub3d)
{
	t_position	t1;
	t_position	t2;
	int			ca;
	int			line_h;
	int			line_off;

	ca = fix_ang(cub3d->var->pa - cub3d->var->ra);
	cub3d->var->dis_h = cub3d->var->dis_h * cos(deg_to_rad(ca));
	line_h = (cub3d->input->map->size_x * cub3d->input->map->size_y * 320)
		/ (cub3d->var->dis_h);
	if (line_h > 320)
		line_h = 320;
	 line_off = 160 - (line_h >> 1);
	t1.x_p = cub3d->var->r * cub3d->input->map->size_y
		+ cub3d->input->map->size_x * GRID_P;
	t2.x_p = line_off;
	t1.y_p = cub3d->var->r * cub3d->input->map->size_y
		+ cub3d->input->map->size_x * GRID_P;
	t2.y_p = line_off + line_h;
	printf("t1.x_p: %d t2.x_p: %d t1.y_p: %d t2.y_p: %d",t1.x_p,t2.x_p,t1.y_p,t2.y_p);
	bresenham_line (t1, t2, cub3d, YELLOW);
}
