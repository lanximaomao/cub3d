#include "cub3D.h"

// to be fix: change exit(1) to clean_exit function
void	init_cub(t_cub *cub)
{
	cub->img = ft_calloc(sizeof(t_img), 1);
	if (!cub->img)
		ft_exit("Error: malloc fail", 1);
	cub->var = ft_calloc(sizeof(t_vars), 1);
	if (!cub->var)
		ft_exit("Error: malloc fail", 1);
	cub->input = ft_calloc(sizeof(t_input), 1);
	if (!cub->input)
		ft_exit("Error: malloc fail", 1);
	cub->input->map = ft_calloc(sizeof(t_map), 1);
	if (!cub->input->map)
		ft_exit("Error: malloc fail", 1);
	cub->input->position = ft_calloc(sizeof(t_position), 1);
	if (!cub->input->position)
		ft_exit("Error: malloc fail", 1);
	init_input(cub->input);
}

void	init_input(t_input *input)
{
	input->count = 0;
	input->t_north = NULL;
	input->t_south = NULL;
	input->t_west = NULL;
	input->t_east = NULL;
	input->color_c = NULL;
	input->color_f = NULL;
	input->position->x_p = -1;
	input->position->y_p = -1;
	init_map(input->map);
}

void	init_map(t_map *map)
{
	map->size_x = 0;
	map->size_y = 0;
	map->direction = -1;
	map->matrix = NULL;
	map->map_1d = ft_strdup(""); // to be freed
	if (!map->map_1d)
		exit(1);
}
