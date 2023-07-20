#include "cub3D.h"

float	deg_to_rad(float a)
{
	return (a * M_PI / 180.0);
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
	cub->var->ra = fix_ang(cub->var->pa + 30);
	while (++(cub->var->r) < 960)
	{
		vertical(cub);
		check_hit(cub, cub->input->map->size_x, &(cub->var->dis_v));
		cub->var->vx = cub->var->rx;
		cub->var->vy = cub->var->ry;
		horizontal(cub);
		check_hit(cub, cub->input->map->size_y, &(cub->var->dis_h));
		if (cub->var->dis_v < cub->var->dis_h)
		{
			cub->var->rx = cub->var->vx;
			cub->var->ry = cub->var->vy;
			cub->var->dis_h = cub->var->dis_v;
		}
		//printf("dis %f\n",cub->var->dis_h);
		draw_ray(cub);
		draw_walls(cub);
		cub->var->ra = fix_ang(cub->var->ra - 0.0625);
	}
}
