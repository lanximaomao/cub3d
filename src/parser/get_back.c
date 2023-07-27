/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_back.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:31:11 by asarikha          #+#    #+#             */
/*   Updated: 2023/07/27 11:34:50 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	matrix_revert(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (++i < cub->input->map->size_y)
	{
		j = -1;
		while (++j < cub->input->map->size_x)
		{
			if (cub->input->map->matrix[i][j] == '2')
				cub->input->map->matrix[i][j] = '1';
			else if (cub->input->map->matrix[i][j] == '@')
				cub->input->map->matrix[i][j] = '0';
			else if (cub->input->map->matrix[i][j] == '_' + 1)
				cub->input->map->matrix[i][j] = '_';
		}
	}
	return (1);
}
