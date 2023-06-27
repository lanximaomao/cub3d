/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarsarikhani <azarsarikhani@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:31:11 by asarikha          #+#    #+#             */
/*   Updated: 2023/06/27 10:59:06 by azarsarikha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int main(int argc, char** argv)
{
	void	*mlx;
	void	*win;

	(void)argc;
	(void)argv;
	write(1,"z",1);
	mlx = mlx_init();
	win = mlx_new_window(mlx,200,200,"cub3D");
	mlx_pixel_put(mlx,win,20,20,0x660066);
	validate();
	mlx_loop(mlx);
	//render();
	return (0);
}
