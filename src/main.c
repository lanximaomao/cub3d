/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/07/05 16:21:05 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "cub3D.h"
#include "parser.h"

void	hook_and_loop(t_cub *cub3d)
{
	mlx_hook(cub3d->win_ptr, EVENT_CLOSE_BTN, 0, end_cub3d, &cub3d);
	mlx_key_hook(cub3d->win_ptr, key_event, &cub3d);
	mlx_mouse_hook(cub3d->win_ptr, mouse_event, &cub3d);
	mlx_loop(cub3d->mlx_ptr);
}

void	clean_init_cub3d(t_cub *cub3d)
{
	cub3d->mlx_ptr = NULL;
	cub3d->win_ptr = NULL;
	cub3d->img->img_ptr = NULL;
	cub3d->img->addr = NULL;
	cub3d->input->position->x_p = -1;
	cub3d->input->position->y_p = -1;
	cub3d->mlx_ptr = mlx_init();
	if (!cub3d->mlx_ptr)
		clean_exit(message("MLX: error connecting to mlx.", "", 1), cub3d);
	cub3d->win_ptr = mlx_new_window(cub3d->mlx_ptr, WIN_SIZE_X,
			WIN_SIZE_Y, "cub3d");
	if (!cub3d->win_ptr)
		clean_exit(message("MLX: error creating window.", "", 1), cub3d);
	if (cub3d->mlx_ptr && cub3d->img)
		mlx_destroy_image(cub3d->mlx_ptr, cub3d->img);
	if (cub3d->img->addr)
		cub3d->img->addr = NULL;
	cub3d->img = mlx_new_image(cub3d->mlx_ptr, WIN_SIZE_X, WIN_SIZE_Y);
	if (!(cub3d->img))
		clean_exit(message("image creation error.", "", 1), cub3d);
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
	if (parser(fd, &cub) == -1)
	{
		printf("Error\n");
		return (-1);
	}
	close(fd);
	clean_init_cub3d(&cub);
	printf("cub.input->position->x_p : %d",cub.input->position->x_p);
	printf("calling render\n");
	//validate();
	render(&cub);
	hook_and_loop(&cub);
	return (0);
}
