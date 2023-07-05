/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:31:11 by asarikha          #+#    #+#             */
/*   Updated: 2023/07/05 10:46:28 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	creat_grid(t_cub *cub3d, int x_from, int y_from, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < GRID_P)
	{
		j = 0;
		while (j < GRID_P)
		{
			creat_img(cub3d, x_from + i, y_from + j, color);
		}
	}
}

static void	creat_player(t_cub *cub3d, int x_from, int y_from, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < PLAYER_P)
	{
		j = 0;
		while (j < PLAYER_P)
		{
			creat_img(cub3d, x_from + i, y_from + j, color);
		}
	}
}

void	draw_map2d(t_cub *cub3d)
{
	int	x;
	int	y;
	int	i;
	int	j;
	int	color;

	i = 0;
	while (i < cub3d->input->map->size_x)
	{
		j = 0;
		while (j < cub3d->input->map->size_y)
		{
			if (cub3d->input->map->matrix[i][j] == '1')
				clolor = BLACK;
			else if (cub3d->input->map->matrix[i][j] == '0')
				color = WHITE;
			creat_grid(cub3d, i * GRID_P, i * GRID_P, color);
			j++;
		}
		i++;
	}
}

void	draw_player2d(t_cub *cub3d)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	if (cub3d->input->position->x_p != -1)
		return (creat_playr(cub3d, cub3d->input->position->x_p - 2
				, cub3d->input->position->y_p - 2, color));
	while (i < cub3d->input->map->size_x)
	{
		j = 0;
		while (j < cub3d->input->map->size_y)
		{
			if (cub3d->input->map->matrix[i][j] == 'N'
			|| cub3d->input->map->matrix[i][j] == 'S'
			|| cub3d->input->map->matrix[i][j] == 'E'
			|| cub3d->input->map->matrix[i][j] == 'W')
			{
				clolor = GREEN;
				creat_playr(cub3d, i * GRID_P + 30, j * GRID_P + 30, color);
			}
			j++;
		}
		i++;
	}
}
