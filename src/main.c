/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/07/05 14:19:52 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../includes/cub3D.h"
#include "../includes/parser.h"

void	hook_and_loop(t_cub *cub3d)
{
	mlx_hook(cub3d->win_ptr, EVENT_CLOSE_BTN, 0, end_cub3d, &cub3d);
	mlx_key_hook(cub3d->win_ptr, key_event, &cub3d);
	mlx_mouse_hook(cub3d->win_ptr, mouse_event, &cub3d);
	mlx_loop(cub3d->mlx_ptr);
}

int	main(int argc, char **argv)
{
	t_cub	cub;
	int		fd;

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
	// if (parser(fd, &cub) == -1)
	// {
	// 	printf("Error\n");
	// 	return (-1);
	// }
	close(fd);
	cub.input->position->x_p = -1;
	cub.input->position->y_p = -1;
	validate();
	render(&cub);
	hook_and_loop(&cub);
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
