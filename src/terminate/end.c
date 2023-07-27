/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linlinsun <linlinsun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/07/28 00:25:06 by linlinsun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	free_input(t_cub *cub)
{
	free_str(cub->input->map->map_1d);
	free_char(cub->input->map->matrix);
	free(cub->input->color_f);
	free(cub->input->color_c);
	free(cub->input->t_east);
	free(cub->input->t_west);
	free(cub->input->t_south);
	free(cub->input->t_north);
	free(cub->input->map);
	free(cub->input->position);
	free(cub->var->wall);
	free(cub->var);
	free(cub->input);
}

static void	free_tex_matrix(int **matrix, int height)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (i < height)
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix);
}

static void	free_tex(t_cub *cub)
{
	free_str(cub->tex_e->type);
	free_str(cub->tex_w->type);
	free_str(cub->tex_s->type);
	free_str(cub->tex_n->type);
	free_tex_matrix(cub->tex_e->matrix, cub->tex_e->height);
	free_tex_matrix(cub->tex_w->matrix, cub->tex_w->height);
	free_tex_matrix(cub->tex_s->matrix, cub->tex_s->height);
	free_tex_matrix(cub->tex_n->matrix, cub->tex_n->height);
	mlx_destroy_image(cub->mlx_ptr, cub->tex_e->img->img_ptr);
	mlx_destroy_image(cub->mlx_ptr, cub->tex_s->img->img_ptr);
	mlx_destroy_image(cub->mlx_ptr, cub->tex_n->img->img_ptr);
	mlx_destroy_image(cub->mlx_ptr, cub->tex_w->img->img_ptr);
	free(cub->tex_e->img);
	free(cub->tex_w->img);
	free(cub->tex_n->img);
	free(cub->tex_s->img);
	free(cub->tex_e);
	free(cub->tex_w);
	free(cub->tex_s);
	free(cub->tex_n);
}

int	end(int exit_code, t_cub *cub)
{
	if (!cub)
		exit(exit_code);
	free_tex(cub); // need to be here so that mlx_ptr is stil valid
	if (cub->img->img_ptr && cub->win_ptr && cub->mlx_ptr)
	{
		mlx_destroy_image(cub->mlx_ptr, cub->img->img_ptr);
		mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
	}
	else if (cub->win_ptr && cub->mlx_ptr)
		mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
	else if (cub->img->img_ptr && cub->mlx_ptr)
		mlx_destroy_image(cub->mlx_ptr, cub->img->img_ptr);
	cub->mlx_ptr = NULL;
	cub->win_ptr = NULL;
	cub->img->addr = NULL;
	free_input(cub);
	free(cub->key);
	exit(exit_code);
}
