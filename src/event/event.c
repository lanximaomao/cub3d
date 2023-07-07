/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:31:11 by asarikha          #+#    #+#             */
/*   Updated: 2023/07/07 13:26:15 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	fix_ang(int a)
{
	if (a > 359)
	{
		a -= 360;
	}
	if (a < 0)
	{
		a += 360;
	}
	return (a);
}

int	mouse_event(int keycode, int x, int y, t_cub *cub3d)
{
	x = 0;
	y = 0;
	keycode = 0;
	// if (keycode == MOUSE_WHEEL_UP)
	// {
	// }
	// else if (keycode == MOUSE_WHEEL_DOWN)
	// {
	// }
	// else if (keycode == MOUSE_BTN)
	// {
	// }
	// else
		return (0);
	
	render(cub3d);
	return (0);
}

int	key_event(int keycode, t_cub *cub3d)
{
	if (keycode == KEY_ESC)
		end_cub3d(cub3d);
	else if (keycode == KEY_UP || keycode == KEY_W)
	{
		cub3d->var->px += cub3d->var->pdx * 5;
		cub3d->var->py += cub3d->var->pdy * 5;
	}
	else if (keycode == KEY_DOWN || keycode == KEY_S)
	{
		cub3d->var->px -= cub3d->var->pdx * 5;
		cub3d->var->py -= cub3d->var->pdy * 5;
	}
	else if (keycode == KEY_LEFT || keycode == KEY_A)
		cub3d->var->pa += 5;
	else if (keycode == KEY_RIGHT || keycode == KEY_D)
		cub3d->var->pa -= 5;
	if (keycode == KEY_LEFT || keycode == KEY_A
		|| keycode == KEY_RIGHT || keycode == KEY_D)
	{
		cub3d->var->pa = fix_ang(cub3d->var->pa);
		cub3d->var->pdx = cos(deg_to_rad(cub3d->var->pa));
		cub3d->var->pdy = -sin(deg_to_rad(cub3d->var->pa));
	}
	cub3d->input->position->y_p = cub3d->var->py - 2;
	cub3d->input->position->x_p = cub3d->var->px - 2;
	printf("cub3d->var->pdx %f cub3d->var->pdy%f\n", cub3d->var->pdx, cub3d->var->pdx);
	printf("cub3d->input->position->x_p %f cub3d->input->position->x_p%f\n", cub3d->var->px, cub3d->var->py);
	render(cub3d);
	return (0);
}
