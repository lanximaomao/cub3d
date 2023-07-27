/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linlinsun <linlinsun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/07/28 00:24:18 by linlinsun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	fill_tex_matrix(t_tex *tex, int y, int x)
{
	int	i;

	tex->matrix = malloc(sizeof(int *) * tex->height);
	if (!tex->matrix)
		return (0);
	i = -1;
	while (++i < tex->height)
	{
		tex->matrix[i] = malloc(sizeof(int) * tex->width);
		if (!tex->matrix[i])
			return (0);
	}
	while (y < tex->height)
	{
		x = 0;
		while (x < tex->width)
		{
			tex->matrix[y][x] = *(unsigned int *)(tex->img->addr
					+ (tex->img->line_length * y) + (x * (tex->img->bpp / 8)));
			x++;
		}
		y++;
	}
	return (1);
}

int	get_tex_data(t_cub *cub, t_tex *tex, char *file, char *type)
{
	tex->type = NULL;
	tex->matrix = NULL;
	tex->img->img_ptr = mlx_xpm_file_to_image(cub->mlx_ptr, file, &(tex->width),
			&(tex->height));
	if (!tex->img->img_ptr)
	{
		message("cann't open texture file\n", 3);
		return (0);
	}
	tex->img->addr = mlx_get_data_addr(tex->img->img_ptr, &(tex->img->bpp),
			&(tex->img->line_length), &(tex->img->endian));
	if (!tex->img->addr)
	{
		message("cann't get texture data\n", 3);
		return (0);
	}
	tex->type = ft_strdup(type);
	if (fill_tex_matrix(tex, 0, 0) == 0)
	{
		message("malloc fail\n", 3);
		return (0);
	}
	return (1);
}
