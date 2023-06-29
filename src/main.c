/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:31:11 by asarikha          #+#    #+#             */
/*   Updated: 2023/06/29 15:54:45 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	hook_and_loop(t_cub *cub3d)
{
	mlx_hook(cub3d->win_ptr, EVENT_CLOSE_BTN, 0, end_cub3d, &cub3d);
	mlx_key_hook(cub3d->win_ptr, key_event, &cub3d);
	mlx_mouse_hook(cub3d->win_ptr, mouse_event, &cub3d);
	mlx_loop(cub3d->mlx_ptr);
}

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*win;
	t_cub	cub3d;

	(void)argc;
	(void)argv;
	write(1,"z",1);
	mlx = mlx_init();
	win = mlx_new_window(mlx,200,200,"cub3D");
	mlx_pixel_put(mlx,win,20,20,0x660066);
	validate();
	mlx_loop(mlx);
	render(&cub3d);
	hook_and_loop(&cub3d);
	return (0);
}