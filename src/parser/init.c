#include "cub3D.h"

void	init_cub(t_cub *cub)
{
	cub->img = malloc(sizeof(t_img) * 1);
	if (!cub->img)
		ft_exit("Error\n-----> malloc fail", 1);
	cub->var = malloc(sizeof(t_vars) * 1);
	if (!cub->var)
		ft_exit("Error\n-----> malloc fail", 1);
	cub->input = malloc(sizeof(t_input) * 1);
	if (!cub->input)
		ft_exit("Error\n-----> malloc fail", 1);
	cub->input->map = malloc(sizeof(t_map) * 1);
	if (!cub->input->map)
		ft_exit("Error\n-----> malloc fail", 1);
	cub->input->position = malloc(sizeof(t_position) * 1);
	if (!cub->input->position)
		ft_exit("Error\n-----> malloc fail", 1);
	cub->key = ft_calloc(sizeof(t_keys), 1);
	if (!cub->key)
		exit (1);
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
	map->map_1d = ft_strdup("");
	if (!map->map_1d)
		exit(1);
}
