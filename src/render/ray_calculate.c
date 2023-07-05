/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calculate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:31:11 by asarikha          #+#    #+#             */
/*   Updated: 2023/07/05 15:43:17 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static	float	deg_to_rad(float a)
{
	return (a * M_PI / 180.0);
}

static void	check_hit(t_cub *cub3d)
{
	while (cub3d->var->dof < 8)
	{
		cub3d->var->mx = (int)(cub3d->var->rx) >> 6;
		cub3d->var->my = (int)(cub3d->var->ry) >> 6;
		cub3d->var->mp = cub3d->var->my * cub3d->input->map->size_x
			+ cub3d->var->mx;
		if (cub3d->var->mp > 0 && cub3d->var->mp < cub3d->input->map->size_x
			* cub3d->input->map->size_y
			&& cub3d->input->map->matrix[cub3d->var->my][cub3d->var->mx] == '1')
		{
			cub3d->var->dof = 8;
			cub3d->var->dis_v = cos(deg_to_rad(cub3d->var->ra))
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
		cub3d->var->rx = (((int)cub3d->var->px >> 6) << 6) + 64;
		cub3d->var->ry = (cub3d->var->px - cub3d->var->rx)
			* cub3d->var->tan + cub3d->var->py;
		cub3d->var->xo = 64;
		cub3d->var->yo = -cub3d->var->xo * cub3d->var->tan;
	}
	else if (cos(deg_to_rad(cub3d->var->ra)) < -0.001)
	{
		cub3d->var->rx = (((int)cub3d->var->px >> 6) << 6) - 0.0001;
		cub3d->var->ry = (cub3d->var->px - cub3d->var->rx)
			* cub3d->var->tan + cub3d->var->py;
		cub3d->var->xo = -64;
		cub3d->var->yo = -cub3d->var->xo * cub3d->var->tan;
	}
	else
	{
		cub3d->var->rx = cub3d->var->px;
		cub3d->var->ry = cub3d->var->py;
		cub3d->var->dof = 8;
	}
}

void	horizontal(t_cub *cub3d)
{
	cub3d->var->dof = 0;
	cub3d->var->dis_h = 100000;
	cub3d->var->tan = 1.0 / cub3d->var->tan;
	if (sin(deg_to_rad(cub3d->var->ra)) > 0.001)
	{
		cub3d->var->ry = (((int)cub3d->var->py >> 6) << 6) - 0.0001;
		cub3d->var->rx = (cub3d->var->py - cub3d->var->ry)
			*cub3d->var->tan + cub3d->var->px;
		cub3d->var->yo = -64;
		cub3d->var->xo = -cub3d->var->yo * cub3d->var->tan;
	}
	else if (sin(deg_to_rad(cub3d->var->ra)) < -0.001)
	{
		cub3d->var->ry = (((int)cub3d->var->py >> 6) << 6) + 64;
		cub3d->var->rx = (cub3d->var->py - cub3d->var->ry)
			*cub3d->var->tan + cub3d->var->px;
		cub3d->var->yo = 64;
		cub3d->var->xo = -cub3d->var->yo * cub3d->var->tan;
	}
	else
	{
		cub3d->var->rx = cub3d->var->px;
		cub3d->var->ry = cub3d->var->py;
		cub3d->var->dof = 8;
	}
}

void	calculate_rays(t_cub *cub3d)
{
	printf("in calculate rays\n");
	cub3d->var->r = -1;
	while (++(cub3d->var->r) < 60)
	{
		vertical(cub3d);
		check_hit(cub3d);
		cub3d->var->vx = cub3d->var->rx;
		cub3d->var->vy = cub3d->var->ry;
		horizontal(cub3d);
		check_hit(cub3d);
		if (cub3d->var->dis_v < cub3d->var->dis_h)
		{
			cub3d->var->rx = cub3d->var->vx;
			cub3d->var->ry = cub3d->var->vy;
			cub3d->var->dis_h = cub3d->var->dis_v;
		}
	}
}
