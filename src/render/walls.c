/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:31:11 by asarikha          #+#    #+#             */
/*   Updated: 2023/07/14 16:40:19 by asarikha         ###   ########.fr       */
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
	//float		previous_line_h;
	//float		previous_line_off;
	int			i;

	//previous_line_h = cub3d->var->line_h;
	//previous_line_off = cub3d->var->line_off;
	// cub3d->var->ca = fix_ang(cub3d->var->pa - cub3d->var->ra);
	// cub3d->var->dis_h = cub3d->var->dis_h * cos(deg_to_rad(cub3d->var->ca));
	// cub3d->var->line_h = 40000 / (cub3d->var->dis_h);
	//printf(" 1. line_h %d ",cub3d->var->line_h);
	ca = fix_ang(cub3d->var->pa - cub3d->var->ra);
	cub3d->var->dis_h = cub3d->var->dis_h * cos(deg_to_rad(ca));
	line_h = 40000 / (cub3d->var->dis_h);
	if (line_h > 1200)
		line_h = 1200;
	line_off = 600 - (line_h >> 1);
	// if (cub3d->var->line_h > 1200)
	// 	cub3d->var->line_h = 1200;
	// //printf(" 2. line_h %d ",line_h);
	// cub3d->var->line_off = 600 - (cub3d->var->line_h / 2);
	//printf(" 3. line_h %d line_off %d ",cub3d->var->line_h, cub3d->var->line_off);
	t1.x_p = (cub3d->var->r) * 4;
	t1.y_p = line_off;
	t2.x_p = cub3d->var->r * 4;
	t2.y_p = line_off + line_h;
	i = -1;
	// if (cub3d->var->r == 0)
	// {
	// 	// t1.y_p = GRID_P * cub3d->input->map->size_y;
	// 	// bresenham_line (t1, t2, cub3d, YELLOW);
	// 	// printf("t1.x_p: %d t2.x_p: %d t1.y_p: %d t2.y_p: %d \n\n",t1.x_p,t2.x_p,t1.y_p,t2.y_p);
	// 	return ;
	// }
	// //printf(" before deduction t1.x_p: %d t2.x_p: %d t1.y_p: %d t2.y_p: %d \n\n",t1.x_p,t2.x_p,t1.y_p,t2.y_p);
	// t1.x_p -= 4;
	// t2.x_p -= 4;
	//printf("after deduction t1.x_p: %d t2.x_p: %d t1.y_p: %d t2.y_p: %d \n\n",t1.x_p,t2.x_p,t1.y_p,t2.y_p);
	while (++i < 4)
	{
		// if (cub3d->var->r == 1)
		// 	continue ;
		//t2.y_p = previous_line_off + previous_line_h - ((previous_line_off + previous_line_h - (cub3d->var->line_off + cub3d->var->line_h)) / 4 * i);
		//t1.y_p = previous_line_off - ((previous_line_off - cub3d->var->line_off) / 4 * i);
		if (t1.x_p < GRID_P * cub3d->input->map->size_x
			&& t1.y_p < GRID_P * cub3d->input->map->size_y)
			t1.y_p = GRID_P * cub3d->input->map->size_y;
		bresenham_line (t1, t2, cub3d, YELLOW);
		//printf("t1.x_p: %d t2.x_p: %d t1.y_p: %d t2.y_p: %d \n",t1.x_p,t2.x_p,t1.y_p,t2.y_p);
		t1.x_p++;
		t2.x_p++;
	}
	// if (cub3d->var->r != 59)
	// 	return ;
	// i = -1;
	// while (++i < 2)
	// {
	// 	t2.y_p = cub3d->var->line_off + cub3d->var->line_h - ((previous_line_off + previous_line_h - (cub3d->var->line_off + cub3d->var->line_h)) / 4 * i);
	// 	t1.y_p = cub3d->var->line_off + ((previous_line_off - cub3d->var->line_off) / 4 * i);
	// 	if (t1.x_p < GRID_P * cub3d->input->map->size_x
	// 		&& t1.y_p < GRID_P * cub3d->input->map->size_y)
	// 		t1.y_p = GRID_P * cub3d->input->map->size_y;
	// 	bresenham_line (t1, t2, cub3d, YELLOW);
	// 	printf("t1.x_p: %d t2.x_p: %d t1.y_p: %d t2.y_p: %d \n",t1.x_p,t2.x_p,t1.y_p,t2.y_p);
	// 	t1.x_p++;
	// 	t2.x_p++;
	// }
	//draw_sky
	//draw_floor
}
