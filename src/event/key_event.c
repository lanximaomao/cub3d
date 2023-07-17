/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:31:11 by asarikha          #+#    #+#             */
/*   Updated: 2023/07/17 16:38:24 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	calculate_next(t_cub *cub3d)
{
	cub3d->key->xo = 0;
	if (cub3d->var->pdx < 0)
		cub3d->key->xo = -20;
	else
		cub3d->key->xo = 20; //x offset to check map
	cub3d->key->yo = 0;
	if (cub3d->var->pdy < 0)
		cub3d->key->yo = -20;
	else
		cub3d->key->yo = 20; //y offset to check map
	cub3d->key->ipx = cub3d->var->px / GRID_P;
	cub3d->key->ipx_add_xo = (cub3d->var->px + cub3d->key->xo) / GRID_P;
	cub3d->key->ipx_sub_xo = (cub3d->var->px - cub3d->key->xo) / GRID_P; //x position and offset
	cub3d->key->ipy = cub3d->var->py / GRID_P;
	cub3d->key->ipy_add_yo = (cub3d->var->py + cub3d->key->yo) / GRID_P;
	cub3d->key->ipy_sub_yo = (cub3d->var->py - cub3d->key->yo) / GRID_P;
}

static void	move_up_down(int dir, t_cub *cub3d)
{
	calculate_next(cub3d);
	if (dir == KEY_DOWN)
	{
		if (cub3d->input->map->matrix[cub3d->key->ipy]
			[cub3d->key->ipx_sub_xo] == 0)
			cub3d->var->px -= cub3d->var->pdx * PLAYE_S;
		if (cub3d->input->map->matrix[cub3d->key->ipy_add_yo]
			[cub3d->key->ipx] == 0)
			cub3d->var->py -= cub3d->var->pdy * PLAYE_S;
	}
	if (dir == KEY_UP)
	{
		if (cub3d->input->map->matrix[cub3d->key->ipy]
			[cub3d->key->ipx_add_xo] == 0)
			cub3d->var->px += cub3d->var->pdx * PLAYE_S;
		if (cub3d->input->map->matrix[cub3d->key->ipy_add_yo]
			[cub3d->key->ipx] == 0)
			cub3d->var->py += cub3d->var->pdy * PLAYE_S;
	}
}

static void	move_right_left(int dir, t_cub *cub3d)
{
	calculate_next(cub3d);
	if (dir == KEY_LEFT)
	{
		cub3d->var->pa += 90;
		cub3d->var->pdx = cos(deg_to_rad(cub3d->var->pa));
		cub3d->var->pdy = -sin(deg_to_rad(cub3d->var->pa));
		cub3d->var->px += cub3d->var->pdx * PLAYE_S;
		cub3d->var->py += cub3d->var->pdy * PLAYE_S;
		cub3d->var->pa -= 90;
	}
	if (dir == KEY_RIGHT)
	{
		cub3d->var->pa -= 90;
		cub3d->var->pdx = cos(deg_to_rad(cub3d->var->pa));
		cub3d->var->pdy = -sin(deg_to_rad(cub3d->var->pa));
		cub3d->var->px += cub3d->var->pdx * PLAYE_S;
		cub3d->var->py += cub3d->var->pdy * PLAYE_S;
		cub3d->var->pa += 90;
	}
}

static void	move_ang(int ang, t_cub *cub3d)
{
	if (ang == KEY_LEFT)
	{
		cub3d->var->pa = fix_ang(cub3d->var->pa + PLAYE_S);
		cub3d->var->pdx = cos(deg_to_rad(cub3d->var->pa));
		cub3d->var->pdy = -sin(deg_to_rad(cub3d->var->pa));
	}
	if (ang == KEY_RIGHT)
	{
		cub3d->var->pa = fix_ang(cub3d->var->pa - PLAYE_S);
		cub3d->var->pdx = cos(deg_to_rad(cub3d->var->pa));
		cub3d->var->pdy = -sin(deg_to_rad(cub3d->var->pa));
	}
}

int	key_event(int keycode, t_cub *cub3d)
{
	cub3d->var->pdx = cos(deg_to_rad(cub3d->var->pa));
	cub3d->var->pdy = -sin(deg_to_rad(cub3d->var->pa));
	if (keycode == KEY_ESC)
		end_cub3d(cub3d);
	else if (keycode == KEY_UP || keycode == KEY_W)
		move_up_down(KEY_UP, cub3d);
	else if (keycode == KEY_DOWN || keycode == KEY_S)
		move_up_down(KEY_DOWN, cub3d);
	else if (keycode == KEY_LEFT)
		move_ang(KEY_LEFT, cub3d);
	else if (keycode == KEY_A)
		move_right_left(KEY_LEFT, cub3d);
	else if (keycode == KEY_RIGHT)
		move_ang(KEY_RIGHT, cub3d);
	else if (keycode == KEY_D)
		move_right_left(KEY_RIGHT, cub3d);
	cub3d->input->position->y_p = cub3d->var->px - 2;
	cub3d->input->position->x_p = cub3d->var->py - 2;
	render(cub3d);
	return (0);
}
