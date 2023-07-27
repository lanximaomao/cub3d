/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:40:35 by asarikha          #+#    #+#             */
/*   Updated: 2023/07/27 13:03:42 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float	fix_ang(float a)
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

float	deg_to_rad(float a)
{
	return (a * M_PI / 180.0);
}

int	key_press(int keycode, t_cub *cub3d)
{
	if (keycode == KEY_W)
		cub3d->key->w = 1;
	if (keycode == KEY_A)
		cub3d->key->a = 1;
	if (keycode == KEY_D)
		cub3d->key->d = 1;
	if (keycode == KEY_S)
		cub3d->key->s = 1;
	if (keycode == KEY_LEFT)
		cub3d->key->left = 1;
	if (keycode == KEY_RIGHT)
		cub3d->key->right = 1;
	if (keycode == KEY_UP)
		cub3d->key->up = 1;
	if (keycode == KEY_DOWN)
		cub3d->key->down = 1;
	key_event(keycode, cub3d);
	return (0);
}

int	key_release(int keycode, t_cub *cub3d)
{
	if (keycode == KEY_W)
		cub3d->key->w = 0;
	if (keycode == KEY_A)
		cub3d->key->a = 0;
	if (keycode == KEY_D)
		cub3d->key->d = 0;
	if (keycode == KEY_S)
		cub3d->key->s = 0;
	if (keycode == KEY_LEFT)
		cub3d->key->left = 0;
	if (keycode == KEY_RIGHT)
		cub3d->key->right = 0;
	if (keycode == KEY_UP)
		cub3d->key->up = 0;
	if (keycode == KEY_DOWN)
		cub3d->key->down = 0;
	return (0);
}
