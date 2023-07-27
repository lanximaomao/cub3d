/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:41:59 by asarikha          #+#    #+#             */
/*   Updated: 2023/07/27 20:27:26 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
** find where wall is
*/
int	find_island(t_cub *cub, int *i, int *j, int *flag)
{
	int	row;
	int	col;

	row = -1;
	while (++row < cub->input->map->size_y)
	{
		col = -1;
		while (++col < cub->input->map->size_x)
		{
			if (cub->input->map->matrix[row][col] == '1')
			{
				if (*flag == 0 && ++*flag)
				{
					*i = row;
					*j = col;
					return (-1);
				}
				else if (*flag == 1 && is_inland(cub, row, col, '2') == -1)
					ft_exit("Error\n-----> more than one islands", 3);
			}
		}
	}
	return (1);
}

int	find_char(t_cub *cub, int *row, int *col, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < cub->input->map->size_y)
	{
		j = 0;
		while (j < cub->input->map->size_x)
		{
			if (cub->input->map->matrix[i][j] == c && is_inland(cub, i, j, '1'
					+ 1) == 1)
			{
				*row = i;
				*col = j;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (-1);
}

int	is_legal_boundary(t_cub *cub, char c, char direction)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < cub->input->map->size_y)
	{
		j = 0;
		while (j < cub->input->map->size_x)
		{
			if ((i == 0 || i == cub->input->map->size_y - 1 || j == 0
					|| j == cub->input->map->size_x - 1)
				&& (cub->input->map->matrix[i][j] == c
				|| cub->input->map->matrix[i][j] == direction))
			{
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (1);
}

/*
** is it necessary to init row and col?
** display_map("flood filled my boundary", cub->input->map->matrix);
*/
int	is_closed(t_cub *cub, int row, int col)
{
	char	direction;

	direction = which_dir(cub);
	while (find_char(cub, &row, &col, '_') == 1)
		flood_fill(cub, row, col, '_');
	row = 0;
	col = 0;
	if (find_char(cub, &row, &col, direction) == 1)
	{
		cub->input->map->matrix[row][col] = '_';
		flood_fill(cub, row, col, '_');
		cub->input->map->matrix[row][col] = direction;
	}
	row = 0;
	col = 0;
	while (find_zero(cub, &row, &col, '0') == 1)
	{
		cub->input->map->matrix[row][col] = '_';
		flood_fill(cub, row, col, '_');
		cub->input->map->matrix[row][col] = '@';
	}
	if (is_legal_boundary(cub, '_' + 1, direction + 1) == -1)
		ft_exit("Error\n-----> wall not closed", 3);
	return (1);
}

/*
** starting point to flood is a '1'
*/
int	valid_map(t_cub *cub)
{
	int	row;
	int	col;
	int	flag;

	row = 0;
	col = 0;
	flag = 0;
	// check for xpm extension
	texture_extension_check(cub);
	texture_validity_check(cub);
	while (find_island(cub, &row, &col, &flag) == -1)
	{
		if (row < cub->input->map->size_y && col < cub->input->map->size_x)
			flood_fill(cub, row, col, cub->input->map->matrix[row][col]);
	}
	row = 0;
	col = 0;
	get_direction(cub, &row, &col);
	if (is_closed(cub, 0, 0) == -1)
		ft_exit("Error\n-----> wall not close", 3);
	if (is_inland(cub, row, col, '2') == -1)
		ft_exit("Error\n-----> player on edge", 3);
	matrix_revert(cub);
	return (1);
}
