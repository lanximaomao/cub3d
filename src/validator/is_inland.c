/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_inland.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:41:47 by asarikha          #+#    #+#             */
/*   Updated: 2023/07/27 13:05:21 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	check_down(t_cub *cub, int row, int col, char c)
{
	while (row < cub->input->map->size_y)
	{
		if (cub->input->map->matrix[row][col] == c)
			return (1);
		row++;
	}
	return (0);
}

static int	check_up(t_cub *cub, int row, int col, char c)
{
	while (row >= 0)
	{
		if (cub->input->map->matrix[row][col] == c)
		{
			return (1);
		}
		row--;
	}
	return (0);
}

static int	check_left(t_cub *cub, int row, int col, char c)
{
	while (col >= 0)
	{
		if (cub->input->map->matrix[row][col] == c)
			return (1);
		col--;
	}
	return (0);
}

static int	check_right(t_cub *cub, int row, int col, char c)
{
	while (col < cub->input->map->size_x)
	{
		if (cub->input->map->matrix[row][col] == c)
			return (1);
		col++;
	}
	return (0);
}

int	is_inland(t_cub *cub, int row, int col, char c)
{
	if (check_up(cub, row, col, c) && check_down(cub, row, col, c)
		&& check_left(cub, row, col, c) && check_right(cub, row, col, c))
		return (1);
	else
		return (-1);
}
