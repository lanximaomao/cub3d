/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calculate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:31:11 by asarikha          #+#    #+#             */
/*   Updated: 2023/07/12 13:07:03 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float	deg_to_rad(float a)
{
	return (a * M_PI / 180.0);
}

static void	check_hit(t_cub *cub3d, int map_side_size, float *dis)
{
	while (cub3d->var->dof < map_side_size)
	{
		cub3d->var->mx = (int)(cub3d->var->rx) >> 5;
		cub3d->var->my = (int)(cub3d->var->ry) >> 5;
		cub3d->var->mp = cub3d->var->my * cub3d->input->map->size_x
			+ cub3d->var->mx;
		// printf("v : cub3d->var->ra : %f ----------", cub3d->var->ra);
		// printf("cub3d->var->pa : %f\n", cub3d->var->pa);
		if (cub3d->var->mp > 0 && cub3d->var->mp < cub3d->input->map->size_x
			* cub3d->input->map->size_y
			&& cub3d->input->map->matrix[cub3d->var->mp / cub3d->input->map->size_x][cub3d->var->mp % cub3d->input->map->size_x] == '1')
		{
			cub3d->var->dof = map_side_size;
			*dis = cos(deg_to_rad(cub3d->var->ra))
				* (cub3d->var->rx - cub3d->var->px)
				- sin(deg_to_rad(cub3d->var->ra))
				* (cub3d->var->ry - cub3d->var->py);
		}
		else
		{
			cub3d->var->rx += cub3d->var->xo;
			cub3d->var->ry += cub3d->var->yo;
			cub3d->var->dof += 1;
		}
	}
}

static	void	vertical(t_cub *cub3d)
{
	cub3d->var->dof = 0;
	cub3d->var->dis_v = 100000;
	cub3d->var->tan = tan(deg_to_rad(cub3d->var->ra));
	if (cos(deg_to_rad(cub3d->var->ra)) > 0.001)
	{
		cub3d->var->rx = (((int)cub3d->var->px >> 5) << 5) + GRID_P;
		cub3d->var->ry = (cub3d->var->px - cub3d->var->rx)
			* cub3d->var->tan + cub3d->var->py;
		cub3d->var->xo = GRID_P;
		cub3d->var->yo = -cub3d->var->xo * cub3d->var->tan;
	}
	else if (cos(deg_to_rad(cub3d->var->ra)) < -0.001)
	{
		cub3d->var->rx = (((int)cub3d->var->px >> 5) << 5) - 0.0001;
		cub3d->var->ry = (cub3d->var->px - cub3d->var->rx)
			* cub3d->var->tan + cub3d->var->py;
		cub3d->var->xo = -GRID_P;
		cub3d->var->yo = -cub3d->var->xo * cub3d->var->tan;
	}
	else
	{
		cub3d->var->rx = cub3d->var->px;
		cub3d->var->ry = cub3d->var->py;
		cub3d->var->dof = cub3d->input->map->size_y;
	}
}

void	horizontal(t_cub *cub3d)
{
	cub3d->var->dof = 0;
	cub3d->var->dis_h = 100000;
	cub3d->var->tan = 1.0 / cub3d->var->tan;
	//printf("sin(deg_to_rad(cub3d->var->ra) %f\n" ,sin(deg_to_rad(cub3d->var->ra)));
	if (sin(deg_to_rad(cub3d->var->ra)) > 0.001)
	{
		cub3d->var->ry = (((int)cub3d->var->py >> 5) << 5) - 0.0001;
		cub3d->var->rx = (cub3d->var->py - cub3d->var->ry)
			*cub3d->var->tan + cub3d->var->px;
		cub3d->var->yo = -GRID_P;
		cub3d->var->xo = -cub3d->var->yo * cub3d->var->tan;
	}
	else if (sin(deg_to_rad(cub3d->var->ra)) < -0.001)
	{
		cub3d->var->ry = (((int)cub3d->var->py >> 5) << 5) + GRID_P;
		cub3d->var->rx = (cub3d->var->py - cub3d->var->ry)
			*cub3d->var->tan + cub3d->var->px;
		cub3d->var->yo = GRID_P;
		cub3d->var->xo = -cub3d->var->yo * cub3d->var->tan;
	}
	else
	{
		cub3d->var->rx = cub3d->var->px;
		cub3d->var->ry = cub3d->var->py;
		cub3d->var->dof = cub3d->input->map->size_x;
	}
}

void	calculate_rays(t_cub *cub3d)
{
	cub3d->var->r = -1;
	cub3d->var->ra = fix_ang(cub3d->var->pa + 30);
	printf("px: %f py: %f",cub3d->var->px, cub3d->var->py);
	while (++(cub3d->var->r) < 60)
	{
		vertical(cub3d);	
		check_hit(cub3d, cub3d->input->map->size_y, &(cub3d->var->dis_v));
		cub3d->var->vx = cub3d->var->rx;
		cub3d->var->vy = cub3d->var->ry;
		horizontal(cub3d);
		check_hit(cub3d, cub3d->input->map->size_x, &(cub3d->var->dis_h));
		if (cub3d->var->dis_v < cub3d->var->dis_h)
		{
			cub3d->var->rx = cub3d->var->vx;
			cub3d->var->ry = cub3d->var->vy;
			cub3d->var->dis_h = cub3d->var->dis_v;
		}
		printf("dis %f\n",cub3d->var->dis_h);
		cub3d->var->ra = fix_ang(cub3d->var->ra -1);
		draw_ray(cub3d);
	}
}
