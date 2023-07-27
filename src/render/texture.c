/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/07/27 20:14:58 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	fill_tex_matrix(t_tex *tex)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < tex->height)
	{
		x = 0;
		while (x < tex->width)
		{
			tex->matrix[y][x] = *(unsigned int *)(tex->img->addr
					+ (tex->line_length * y) + (x * (tex->bpp / 8)));
			x++;
		}
		y++;
	}
}

int	get_tex_data(t_cub *cub, t_tex *tex, char *file, char *type)
{
	int	i;

	tex->type = NULL;
	tex->matrix = NULL;
	tex->img->img_ptr = mlx_xpm_file_to_image(cub->mlx_ptr, file,
			&(tex->width), &(tex->height));
	if (!tex->img->img_ptr)
	{
		message("cann't open texture file\n", 3);
		return (0);
	}
	tex->img->addr
		= mlx_get_data_addr(tex->img->img_ptr, &(tex->bpp),
			&(tex->line_length), &(tex->endian));
	if (!tex->img->addr)
	{
		message("cann't get texture data\n", 3);
		return (0);
	}
	tex->type = ft_strdup(type);
	tex->matrix = malloc(sizeof(int *) * tex->height);
	if (!tex->matrix)
	{
		message("malloc fail\n", 1);
		return (0);
	}
	i = -1;
	while (++i < tex->height)
	{
		tex->matrix[i] = malloc(sizeof(int) * tex->width);
		if (!tex->matrix[i])
			return (0);
	}
	fill_tex_matrix(tex);
	return (1);
}

