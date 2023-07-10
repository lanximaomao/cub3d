/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:31:11 by asarikha          #+#    #+#             */
/*   Updated: 2023/07/10 10:08:34 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	creat_grid(t_cub *cub3d, int x_from, int y_from, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < GRID_P)
	{
		j = -1;
		while (++j < GRID_P)
		{
			pixel_color(cub3d, x_from + i, y_from + j, color);
		}
	}
}

static void	creat_player(t_cub *cub3d, int x_from, int y_from, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < PLAYER_P)
	{
		j = -1;
		while (++j < PLAYER_P)
		{
			pixel_color(cub3d, y_from + j, x_from + i, color);
		}
	}
}

void	draw_map2d(t_cub *cub3d)
{
	int	i;
	int	j;
	int	color;

	i = -1;
	while (++i < cub3d->input->map->size_y)
	{
		j = -1;
		while (++j < cub3d->input->map->size_x)
		{
			if (cub3d->input->map->matrix[i][j] == '1')
				color = GREEN;
			else if (cub3d->input->map->matrix[i][j] == '0')
				color = LEMON_CHIFFON;
			else if (cub3d->input->map->matrix[i][j] == '_')
				color = TOMATO;
			else
				color = WHITE;
			creat_grid(cub3d, j * GRID_P, i * GRID_P, color);
		}
	}
}

void	draw_player2d(t_cub *cub3d)
{
	int	i;
	int	j;
	int	color;

	i = -1;
	color = PURPLE;
	if (cub3d->input->position->x_p != -1)
		return (creat_player(cub3d, cub3d->input->position->x_p
				, cub3d->input->position->y_p, color));
	while (++i < cub3d->input->map->size_y)
	{
		j = -1;
		while (++j < cub3d->input->map->size_x)
		{
			if (cub3d->input->map->matrix[i][j] == 'N'
			|| cub3d->input->map->matrix[i][j] == 'S'
			|| cub3d->input->map->matrix[i][j] == 'E'
			|| cub3d->input->map->matrix[i][j] == 'W')
			{
				creat_player(cub3d, i * GRID_P + GRID_P / 2, j
					* GRID_P + GRID_P / 2, color);
				cub3d->input->position->x_p = i * GRID_P + GRID_P / 2;
				cub3d->input->position->y_p = j * GRID_P + GRID_P / 2;
				cub3d->var->px = cub3d->input->position->y_p;
				cub3d->var->py = cub3d->input->position->x_p;
				break ;
			}
		//printf("cub3d->input->position->x_p %d cub3d->input->position->y_p%d\n", i * GRID_P + GRID_P / 2, j * GRID_P + GRID_P / 2);
		//printf("1-----------------------------------\n");
		}
	}
}
