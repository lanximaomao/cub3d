#include "cub3D.h"

// define error code, 1 for malloc fail, 2 for wrong color, 3 for other validation error, 4 for function fail
// check for memory leak
// check for unclosed maps
// map_forbbiden?
// xpm path validity?

int get_direction(t_cub *cub, int *i, int *j)
{
	int ret;

	ret = 0;
	while (*i < cub->input->map->size_y)
	{
		*j = 0;
		while (*j < cub->input->map->size_x)
		{
			if (cub->input->map->matrix[*i][*j] == 'E'  && ++ret)
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

static int get_texture(t_cub *cub, char*line, int flag)
{
	int i;

	i = 0;
	if (ft_strncmp(cub->input->map->map_1d, "", 1))
		ft_exit("Error: no more input after map", 3);
	if ((flag == 1 && cub->input->t_north)
		|| (flag == 2 && cub->input->t_south)
		|| (flag == 3 && cub->input->t_west)
		|| (flag == 4 && cub->input->t_east))
		ft_exit("Error: texture duplicates", 3);
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

static int line_processor(t_cub *cub, char* line, int *map_start, int *nl_flag)
{
	int i;

	i = 0;
	if (*map_start == 0 && line[i] == '\n')
		return (0);
	while (*map_start == 0 && line[i] == ' ') // skip space
			i++;
	if (*map_start == 0 && line[i] == '\n') // empty line, just return
		return (0);
	if (line[i] == 'N' && line[i+1] == 'O')
		get_texture(cub, line, 1);
	else if (line[i] == 'S' && line[i+1] == 'O')
		get_texture(cub, line, 2);
	else if (line[i] == 'W' && line[i+1] == 'E')
		get_texture(cub, line, 3);
	else if (line[i] == 'E' && line[i+1] == 'A')
		get_texture(cub, line, 4);
	else if (line[i] == 'F')
		get_color(cub, line, 1);
	else if (line[i] == 'C')
		get_color(cub, line, 2);
	else if (++*map_start ) // flag to show map read started
		get_map(cub, line, nl_flag);
	return (0);
}

int parser(int fd, t_cub *cub)
{
	char* line;
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
				ft_exit("Error: empty map", 3);
			get_matrix(cub);
			printf("dir=%f\n", cub->input->map->direction);
			return (0);
		}
		line_start = 1;
		line_processor(cub, line, &map_start, &nl_flag);
		free_str(line);
	}
	return (0);
}
