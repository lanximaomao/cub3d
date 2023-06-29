/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:31:11 by asarikha          #+#    #+#             */
/*   Updated: 2023/06/29 12:36:54 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	clean_exit(int exit_code, t_fractol *cub3d)
{
	if (!cub3d)
		exit(exit_code);
	if (cub3d->img.img_ptr && cub3d->win_ptr && cub3d->mlx_ptr)
	{
		mlx_destroy_image(cub3d->mlx_ptr, cub3d->img.img_ptr);
		mlx_destroy_window(cub3d->mlx_ptr, cub3d->win_ptr);
		cub3d->mlx_ptr = NULL;
		cub3d->win_ptr = NULL;
		cub3d->img.addr = NULL;
		exit (exit_code);
	}
	else if (cub3d->win_ptr && cub3d->mlx_ptr)
	{
		mlx_destroy_window(cub3d->mlx_ptr, cub3d->win_ptr);
		cub3d->win_ptr = NULL;
		cub3d->mlx_ptr = NULL;
		exit (exit_code);
	}
	else if (cub3d->img.img_ptr && cub3d->mlx_ptr)
	{
		mlx_destroy_image(cub3d->mlx_ptr, cub3d->img.img_ptr);
		cub3d->img.img_ptr = NULL;
		exit (exit_code);
	}
	exit (exit_code);
}

int	end_cub3d(t_cub *cub3d)
{
	clean_exit(0, cub3d);
	return (0);
}
