#include "cub3D.h"

static int	get_color_floor(char *line, t_color_rgb *color, t_cub *cub)
{
	char	*line_with_color;
	char	**color_split;

	line_with_color = ft_strtrim(line, "F \n");
	if (!line_with_color)
		ft_exit("Error: ft_strtrim failed", 4);
	color_split = ft_split(line_with_color, ',');
	free(line_with_color);
	if (!color_split)
		ft_exit("Error: ft_split failed", 4);
	if (array_size(color_split) != 3)
		ft_exit("Error: ceiling color missing", 3);
	cub->input->color_f = color;
	color->r = ft_atoi_isnum(color_split[0]);
	color->g = ft_atoi_isnum(color_split[1]);
	color->b = ft_atoi_isnum(color_split[2]);
	if (color->r == -1 || color->g == -1 || color->b == -1)
		ft_exit("Error: wrong color input", 2);
	free_char(color_split);
	return (0);
}

static int	get_color_ceiling(char *line, t_color_rgb *color, t_cub *cub)
{
	char	*line_with_color;
	char	**color_split;

	line_with_color = ft_strtrim(line, "C \n");
	if (!line_with_color)
		ft_exit("Error: ft_strtrim failed", 4);
	color_split = ft_split(line_with_color, ',');
	free_str(line_with_color);
	if (!color_split)
		ft_exit("Error: ft_split failed", 4);
	if (array_size(color_split) != 3)
		ft_exit("Error: ceiling color missing", 3);
	cub->input->color_c = color;
	color->r = ft_atoi_isnum(color_split[0]);
	color->g = ft_atoi_isnum(color_split[1]);
	color->b = ft_atoi_isnum(color_split[2]);
	if (color->r == -1 || color->g == -1 || color->b == -1)
		ft_exit("Error: wrong color input", 2);
	free_char(color_split);
	return (0);
}
/*
** Flag 1 for F, 2 for c
*/

int	get_color(t_cub *cub, char *line, int flag)
{
	t_color_rgb	*color;

	if (ft_strncmp(cub->input->map->map_1d, "", 1))
		ft_exit("Error: all args are already given", 3);
	if ((flag == 1 && cub->input->color_f)
		|| (flag == 2 && cub->input->color_c))
		ft_exit("Error: duplicate color definition", 2);
	if (how_many(line, ',') != 2)
		ft_exit("Error: wrong input for RGB color", 2);
	color = ft_calloc(sizeof(t_color_rgb), 1);
	if (!color)
		ft_exit("Error: malloc fail", 1);
	if (flag == 1 && get_color_floor(line, color, cub) == -1)
		exit(-1);
	if (flag == 2 && get_color_ceiling(line, color, cub) == -1)
		exit(-1);
	cub->input->count++;
	return (0);
}
