/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:31:11 by asarikha          #+#    #+#             */
/*   Updated: 2023/07/05 13:52:03 by asarikha         ###   ########.fr       */
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
