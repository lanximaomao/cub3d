/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linlinsun <linlinsun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:42:06 by asarikha          #+#    #+#             */
/*   Updated: 2023/07/28 00:27:09 by linlinsun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** display_map("map", cub.input->map->matrix);
** display_texture(cub.input);
** display_color(cub.input);
*/

#include "cub3D.h"

void	hook_and_loop(t_cub *cub)
{
	mlx_hook(cub->win_ptr, EVENT_CLOSE_BTN, 0, close_window, cub);
	mlx_hook(cub->win_ptr, EVENT_KEY_PRESS, 1L << 0, key_press, cub);
	mlx_loop(cub->mlx_ptr);
}

void	init_render(t_cub *cub)
{
	cub->mlx_ptr = mlx_init();
	if (!cub->mlx_ptr)
		end(message("MLX: error connecting to mlx.", 1), cub);
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, WIN_SIZE_X, WIN_SIZE_Y,
			"cub");
	if (!cub->win_ptr)
		end(message("MLX: error creating window.", 1), cub);
	cub->img->img_ptr = mlx_new_image(cub->mlx_ptr, WIN_SIZE_X, WIN_SIZE_Y);
	if (!(cub->img->img_ptr))
		end(message("image creation error.", 1), cub);
	if (get_tex_data(cub, cub->tex_e, cub->input->t_east, "EA") == 0
		|| get_tex_data(cub, cub->tex_w, cub->input->t_west, "WE") == 0
		|| get_tex_data(cub, cub->tex_n, cub->input->t_north, "NO") == 0
		|| get_tex_data(cub, cub->tex_s, cub->input->t_south, "SO") == 0)
		end(message("texture error\n", 3), cub);
	cub->var->pa = cub->input->map->direction;
	cub->var->pdx = cos(deg_to_rad(cub->var->pa));
	cub->var->pdy = -sin(deg_to_rad(cub->var->pa));
}

int	main(int argc, char **argv)
{
	t_cub	cub;
	int		fd;

	if (argc != 2)
		ft_exit("Error\n-----> wrong number of arguments", 1);
	if (valid_filetype(argv[1]) == -1)
		ft_exit("Error\n-----> wrong type of file", 3);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_exit("Error: cannot open file", 1);
	if (parser(fd, &cub) && close(fd) != -1 && valid_map(&cub))
	{
		init_render(&cub);
		render(&cub);
		hook_and_loop(&cub);
		end(0, &cub);
	}
	return (0);
}
