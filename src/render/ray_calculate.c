/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calculate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/07/27 18:16:52 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	set_distance(t_cub *cub)
{
	if (cub->var->dis_v < cub->var->dis_h)
	{
		cub->var->rx = cub->var->vx;
		cub->var->ry = cub->var->vy;
		cub->var->dis_h = cub->var->dis_v;
		if (cub->var->ra < 90
			|| (cub->var->ra > 270 && cub->var->ra < 360))
			cub->var->dir = 'W';
		else if (cub->var->ra > 90 && cub->var->ra < 270)
			cub->var->dir = 'E';
	}
	else
	{
		if (cub->var->ra < 180)
			cub->var->dir = 'S';
		else
			cub->var->dir = 'N';
	}
}

static void	check_hit(t_cub *cub, int map_side_size, float *dis)
{
	while (cub->var->dof < map_side_size)
	{
		cub->var->mx = (int)(cub->var->rx) / GRID_P;
		cub->var->my = (int)(cub->var->ry) / GRID_P;
		cub->var->mp = cub->var->my * cub->input->map->size_x
			+ cub->var->mx;
		if (cub->var->mp > 0 && cub->var->mp < cub->input->map->size_x
			* cub->input->map->size_y
			&& cub->input->map->matrix
			[cub->var->mp / cub->input->map->size_x]
			[cub->var->mp % cub->input->map->size_x] == '1')
		{
			cub->var->dof = map_side_size;
			*dis = cos(deg_to_rad(cub->var->ra))
				* (cub->var->rx - cub->var->px)
				- sin(deg_to_rad(cub->var->ra))
				* (cub->var->ry - cub->var->py);
		}
		else
		{
			cub->var->rx += cub->var->xo;
			cub->var->ry += cub->var->yo;
			cub->var->dof += 1;
		}
	}
}

static	void	vertical(t_cub *cub)
{
	cub->var->dof = 0;
	cub->var->dis_v = 100000;
	cub->var->tan = tan(deg_to_rad(cub->var->ra));
	if (cos(deg_to_rad(cub->var->ra)) > 0.001)
	{
		cub->var->rx = (((int)cub->var->px / GRID_P) * GRID_P) + GRID_P;
		cub->var->ry = (cub->var->px - cub->var->rx)
			* cub->var->tan + cub->var->py;
		cub->var->xo = GRID_P;
		cub->var->yo = -cub->var->xo * cub->var->tan;
	}
	else if (cos(deg_to_rad(cub->var->ra)) < -0.001)
	{
		cub->var->rx = (((int)cub->var->px / GRID_P) * GRID_P) - 0.0001;
		cub->var->ry = (cub->var->px - cub->var->rx)
			* cub->var->tan + cub->var->py;
		cub->var->xo = -GRID_P;
		cub->var->yo = -cub->var->xo * cub->var->tan;
	}
	else
	{
		cub->var->rx = cub->var->px;
		cub->var->ry = cub->var->py;
		cub->var->dof = cub->input->map->size_x;
	}
}

void	horizontal(t_cub *cub)
{
	cub->var->dof = 0;
	cub->var->dis_h = 100000;
	cub->var->tan = 1.0 / cub->var->tan;
	if (sin(deg_to_rad(cub->var->ra)) > 0.001)
	{
		cub->var->ry = (((int)cub->var->py / GRID_P) * GRID_P) - 0.0001;
		cub->var->rx = (cub->var->py - cub->var->ry)
			*cub->var->tan + cub->var->px;
		cub->var->yo = -GRID_P;
		cub->var->xo = -cub->var->yo * cub->var->tan;
	}
	else if (sin(deg_to_rad(cub->var->ra)) < -0.001)
	{
		cub->var->ry = (((int)cub->var->py / GRID_P) * GRID_P) + GRID_P;
		cub->var->rx = (cub->var->py - cub->var->ry)
			*cub->var->tan + cub->var->px;
		cub->var->yo = GRID_P;
		cub->var->xo = -cub->var->yo * cub->var->tan;
	}
	else
	{
		cub->var->rx = cub->var->px;
		cub->var->ry = cub->var->py;
		cub->var->dof = cub->input->map->size_y;
	}
}

void	calculate_rays(t_cub *cub)
{
	cub->var->r = -1;
	cub->var->ra = fix_ang(cub->var->pa + FOV / 2);
	while (++(cub->var->r) < WIN_SIZE_X)
	{
		vertical(cub);
		check_hit(cub, cub->input->map->size_x, &(cub->var->dis_v));
		cub->var->vx = cub->var->rx;
		cub->var->vy = cub->var->ry;
		horizontal(cub);
		check_hit(cub, cub->input->map->size_y, &(cub->var->dis_h));
		set_distance(cub);
		draw_ray(cub);
		draw_walls(cub);
		cub->var->ra = fix_ang(cub->var->ra - FOV / WIN_SIZE_X);
	}
}
