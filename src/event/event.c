/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:31:11 by asarikha          #+#    #+#             */
/*   Updated: 2023/07/03 11:10:06 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	mouse_event(int keycode, int x, int y, t_cub *cub3d)
{
	if (keycode == MOUSE_WHEEL_UP)
	{
	}
	else if (keycode == MOUSE_WHEEL_DOWN)
	{
	}
	else if (keycode == MOUSE_BTN)
	{
	}
	else
		return (0);
	render(cub3d);
	return (0);
}

int	key_event(int keycode, t_cub *cub3d)
{
	if (keycode == KEY_ESC)
	{
		end_cub3d(cub3d);
	}
	// else if (keycode == KEY_PLUS)
	// 	zoom(mlx, 0.5);
	// else if (keycode == KEY_MINUS)
	// 	zoom(mlx, 2);
	// else if (keycode == KEY_UP || keycode == KEY_W)
	// 	move(mlx, 0.2, 'U');
	// else if (keycode == KEY_DOWN || keycode == KEY_S)
	// 	move(mlx, 0.2, 'D');
	// else if (keycode == KEY_LEFT || keycode == KEY_A)
	// 	move(mlx, 0.2, 'L');
	// else if (keycode == KEY_RIGHT || keycode == KEY_D)
	// 	move(mlx, 0.2, 'R');
	// else if (!key_event_extend(keycode, mlx))
	// 	return (1);
	else
		return (1);
	render(cub3d);
	return (0);
}
