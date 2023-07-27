/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linlinsun <linlinsun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/07/28 00:22:32 by linlinsun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	creat_grid(t_cub *cub, int x_from, int y_from, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < GRID_P - 1)
	{
		j = -1;
		while (++j < GRID_P - 1)
		{
			pixel_color(cub, x_from + i, y_from + j, color);
		}
	}
}

static void	creat_player(t_cub *cub, int x_from, int y_from, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < PLAYER_P)
	{
		j = -1;
		while (++j < PLAYER_P)
		{
			pixel_color(cub, y_from + j, x_from + i, color);
		}
	}
}

void	draw_map2d(t_cub *cub)
{
	int	i;
	int	j;
	int	color;

	i = -1;
	while (++i < cub->input->map->size_y)
	{
		j = -1;
		while (++j < cub->input->map->size_x)
		{
			if (cub->input->map->matrix[i][j] == '1')
				color = GREEN;
			else if (cub->input->map->matrix[i][j] == '0')
				color = WHITE;
			else if (cub->input->map->matrix[i][j] == '_')
				color = TOMATO;
			else
				color = WHITE;
			creat_grid(cub, j * GRID_P, i * GRID_P, color);
		}
	}
}

void	set_coordinates(t_cub *cub, int i, int j)
{
	cub->input->position->x_p = i * GRID_P + GRID_P / 2;
	cub->input->position->y_p = j * GRID_P + GRID_P / 2;
	cub->var->px = cub->input->position->y_p;
	cub->var->py = cub->input->position->x_p;
}

void	draw_player2d(t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	if (cub->input->position->x_p != -1)
		return (creat_player(cub, cub->input->position->x_p,
				cub->input->position->y_p, PURPLE));
	while (++i < cub->input->map->size_y)
	{
		j = -1;
		while (++j < cub->input->map->size_x)
		{
			if (cub->input->map->matrix[i][j] == 'N'
				|| cub->input->map->matrix[i][j] == 'S'
				|| cub->input->map->matrix[i][j] == 'E'
				|| cub->input->map->matrix[i][j] == 'W')
			{
				creat_player(cub, i * GRID_P + GRID_P / 2, j * GRID_P + GRID_P
					/ 2, PURPLE);
				set_coordinates(cub, i, j);
				cub->input->map->matrix[i][j] = 0;
				break ;
			}
		}
	}
}
