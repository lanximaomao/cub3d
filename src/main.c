/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linlinsun <linlinsun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:31:11 by asarikha          #+#    #+#             */
/*   Updated: 2023/06/29 12:45:11 by linlinsun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"
#include "../includes/parser.h"

int main(int argc, char** argv)
{
	int fd;
	t_cub cub;

	if (argc != 2)
	{
		printf("wrong number of arguments.\n");
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("cannot open file.\n");
		return (1);
	}
	if (parser(fd, &cub) == -1)
	{
		printf("Error\n");
		return (-1);
	}
	close(fd);
	return (0);
}

//int main(int argc, char** argv)
//{
//	void	*mlx;
//	void	*win;

//	(void)argc;
//	(void)argv;
//	write(1,"z",1);
//	mlx = mlx_init();
//	win = mlx_new_window(mlx,200,200,"cub3D");
//	mlx_pixel_put(mlx,win,20,20,0x660066);
//	validate();
//	mlx_loop(mlx);
//	//render();
//	return (0);
//}
