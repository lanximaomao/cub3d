/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_filetype.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:41:54 by asarikha          #+#    #+#             */
/*   Updated: 2023/07/27 20:29:17 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
** only filename end with .cub, not .cub3 or.crab
*/
int	valid_filetype(char *str)
{
	char	*ret;

	ret = ft_strnstr(str, ".cub", ft_strlen(str));
	if (!ret)
		return (-1);
	if (*(ret + 4) != '\0')
		return (-1);
	return (1);
}

int	texture_extension_check(t_cub *cub)
{
	int	str_end;

	str_end = ft_strlen(cub->input->t_east);
	str_end = str_end - 4;
	if (ft_strncmp(&(cub->input->t_east[str_end]), ".xpm", 4))
		ft_exit("Error\n-----> wrong texture file extension", 4);
	str_end = ft_strlen(cub->input->t_west);
	str_end = str_end - 4;
	if (ft_strncmp(&(cub->input->t_west[str_end]), ".xpm", 4))
		ft_exit("Error\n-----> wrong texture file extension", 4);
	str_end = ft_strlen(cub->input->t_north);
	str_end = str_end - 4;
	if (ft_strncmp(&(cub->input->t_north[str_end]), ".xpm", 4))
		ft_exit("Error\n-----> wrong texture file extension", 4);
	str_end = ft_strlen(cub->input->t_south);
	str_end = str_end - 4;
	if (ft_strncmp(&(cub->input->t_south[str_end]), ".xpm", 4))
		ft_exit("Error\n-----> wrong texture file extension", 4);
	return (1);
}

int texture_validity_check(t_cub *cub)
{
	int fd;

	fd = open(cub->input->t_east, O_RDONLY);
	if (fd == -1)
		ft_exit("texture error", 3);
	else
		close (fd);
	fd = open(cub->input->t_west, O_RDONLY);
	if (fd == -1)
		ft_exit("texture error", 3);
	else
		close (fd);
	fd = open(cub->input->t_south, O_RDONLY);
	if (fd == -1)
		ft_exit("texture error", 3);
	else
		close (fd);
	fd = open(cub->input->t_north, O_RDONLY);
	if (fd == -1)
		ft_exit("texture error", 3);
	else
		close (fd);
	return (1);
}
