/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_direction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:36:23 by asarikha          #+#    #+#             */
/*   Updated: 2023/07/27 11:36:26 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_direction(t_cub *cub, int *i, int *j)
{
	int	ret;

	ret = 0;
	while (*i < cub->input->map->size_y)
	{
		*j = 0;
		while (*j < cub->input->map->size_x)
		{
			if (cub->input->map->matrix[*i][*j] == 'E' && ++ret)
				cub->input->map->direction = 0;
			else if (cub->input->map->matrix[*i][*j] == 'N' && ++ret)
				cub->input->map->direction = 90;
			else if (cub->input->map->matrix[*i][*j] == 'W' && ++ret)
				cub->input->map->direction = 180;
			else if (cub->input->map->matrix[*i][*j] == 'S' && ++ret)
				cub->input->map->direction = 270;
			if (ret)
				return (ret);
			(*j)++;
		}
		(*i)++;
	}
	return (ret);
}
