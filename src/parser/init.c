/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:36:46 by asarikha          #+#    #+#             */
/*   Updated: 2023/07/27 19:24:04 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	cub->key = malloc(sizeof(t_keys) * 1);
	if (!cub->key)
		ft_exit("Error\n-----> malloc fail", 1);
	cub->var->wall = malloc(sizeof(t_wall) * 1);
	if (!cub->var->wall)
		ft_exit("Error\n-----> malloc fail", 1);
	init_input(cub->input);
	init_tex(cub);
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

void	init_tex(t_cub *cub)
{
	cub->tex_e = malloc(sizeof(t_tex));
	if (!cub->tex_e)
		ft_exit("Error\n-----> malloc fail", 1);
	cub->tex_w = malloc(sizeof(t_tex));
	if (!cub->tex_w)
		ft_exit("Error\n-----> malloc fail", 1);
	cub->tex_n = malloc(sizeof(t_tex));
	if (!cub->tex_n)
		ft_exit("Error\n-----> malloc fail", 1);
	cub->tex_s = malloc(sizeof(t_tex));
	if (!cub->tex_s)
		ft_exit("Error\n-----> malloc fail", 1);
	cub->tex_e->img = malloc(sizeof(t_img));
	if (!cub->tex_e->img)
		ft_exit("Error\n-----> malloc fail", 1);
	cub->tex_w->img = malloc(sizeof(t_img));
	if (!cub->tex_w->img)
		ft_exit("Error\n-----> malloc fail", 1);
	cub->tex_n->img = malloc(sizeof(t_img));
	if (!cub->tex_n->img)
		ft_exit("Error\n-----> malloc fail", 1);
	cub->tex_s->img = malloc(sizeof(t_img));
	if (!cub->tex_s->img)
		ft_exit("Error\n-----> malloc fail", 1);
}
