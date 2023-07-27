/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:36:49 by asarikha          #+#    #+#             */
/*   Updated: 2023/07/27 11:41:21 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	line_processor(t_cub *cub, char *line, int *map_start, int *nl_flag)
{
	int	i;

	i = 0;
	if (*map_start == 0 && line[i] == '\n')
		return (0);
	while (*map_start == 0 && line[i] == ' ')
		i++;
	if (*map_start == 0 && line[i] == '\n')
		return (0);
	if (line[i] == 'N' && line[i + 1] == 'O')
		get_texture(cub, line, 1);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		get_texture(cub, line, 2);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		get_texture(cub, line, 3);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		get_texture(cub, line, 4);
	else if (line[i] == 'F')
		get_color(cub, line, 1);
	else if (line[i] == 'C')
		get_color(cub, line, 2);
	else if (++*map_start)
		get_map(cub, line, nl_flag);
	return (0);
}

int	parser(int fd, t_cub *cub)
{
	char	*line;
	int		line_start;
	int		map_start;
	int		nl_flag;

	line = NULL;
	line_start = 0;
	map_start = 0;
	nl_flag = 0;
	init_cub(cub);
	while (42)
	{
		line = get_next_line(fd);
		if (!line)
		{
			if (line_start == 0)
				ft_exit("Error\n-----> empty map", 3);
			get_matrix(cub);
			return (1);
		}
		line_start = 1;
		line_processor(cub, line, &map_start, &nl_flag);
		free_str(line);
	}
	return (1);
}
