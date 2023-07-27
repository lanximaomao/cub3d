/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:36:41 by asarikha          #+#    #+#             */
/*   Updated: 2023/07/27 11:36:42 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_texture(t_cub *cub, char *line, int flag)
{
	int	i;

	i = 0;
	if (ft_strncmp(cub->input->map->map_1d, "", 1))
		ft_exit("Error\n-----> no more input after map", 3);
	if ((flag == 1 && cub->input->t_north) || (flag == 2 && cub->input->t_south)
		|| (flag == 3 && cub->input->t_west) || (flag == 4
			&& cub->input->t_east))
		ft_exit("Error\n-----> texture duplicates", 3);
	if (flag == 1)
		cub->input->t_north = ft_strtrim(line, "NO \n");
	else if (flag == 2)
		cub->input->t_south = ft_strtrim(line, "SO \n");
	else if (flag == 3)
		cub->input->t_west = ft_strtrim(line, "WE \n");
	else if (flag == 4)
		cub->input->t_east = ft_strtrim(line, "EA \n");
	cub->input->count++;
	return (0);
}
