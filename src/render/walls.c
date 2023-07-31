/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/07/31 11:33:13 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_sky_floor(t_cub *cub, t_position	t1, t_position	t2)
{
	t_position		s1;
	t_position		s2;
	t_position		f1;
	t_position		f2;

	s1.x_p = t1.x_p;
	s2.x_p = t1.x_p;
	s1.y_p = 0;
	s2.y_p = t1.y_p - 1;
	if (t1.x_p < GRID_P * cub->input->map->size_x
		&& s2.y_p < GRID_P * cub->input->map->size_y)
			s2.y_p = 0;
	if (t1.x_p < GRID_P * cub->input->map->size_x
		&& s2.y_p >= GRID_P * cub->input->map->size_y)
			s1.y_p = GRID_P * cub->input->map->size_y + 1;
	bresenham_line (s1, s2, cub, calculate_hex_color(cub->input->color_c));
	f1.x_p = t1.x_p;
	f2.x_p = t1.x_p;
	f1.y_p = t2.y_p + 1;
	f2.y_p = WIN_SIZE_Y - 1;
	if (t1.x_p < GRID_P * cub->input->map->size_x
		&& f1.y_p < GRID_P * cub->input->map->size_y)
			f1.y_p = GRID_P * cub->input->map->size_y + 1;
	bresenham_line (f1, f2, cub, calculate_hex_color(cub->input->color_f));
	return ;
}

t_tex	*texture_(t_cub *cub)
{
	if (cub->var->dir == 'N')
		return (cub->tex_n);
	if (cub->var->dir == 'S')
		return (cub->tex_s);
	if (cub->var->dir == 'W')
		return (cub->tex_w);
	if (cub->var->dir == 'E')
		return (cub->tex_e);
	return (0);
}

void	put_textured_wall(t_position	t1, t_position	t2, t_cub *cub)
{
	t_tex	*tex;

	tex = texture_(cub);
	cub->var->wall->ty = 0;
	if (cub->var->dir == 'S' || cub->var->dir == 'N')
		cub->var->wall->tx = (int)(cub->var->rx * tex->width / GRID_P)
			% tex->width;
	else
		cub->var->wall->tx = (int)(cub->var->ry * tex->width / GRID_P)
			% tex->width;
	if (cub->var->ra > 90)
		cub->var->wall->tx = tex->height - 1 - cub->var->wall->tx;
	while (t1.y_p < t2.y_p && (int)cub->var->wall->ty < tex->height)
	{
		if (!(t1.x_p < GRID_P * cub->input->map->size_x
				&& t1.y_p < GRID_P * cub->input->map->size_y))
		{
			pixel_color(cub, t1.x_p, t1.y_p,
				tex->matrix[(int)cub->var->wall->ty]
			[(int)cub->var->wall->tx]);
		}
		cub->var->wall->ty += cub->var->wall->ty_step;
		t1.y_p++;
	}
}

void	draw_walls(t_cub *cub)
{
	t_position	t1;
	t_position	t2;

	cub->var->ca = fix_ang(cub->var->pa - cub->var->ra);
	cub->var->dis_h = cub->var->dis_h * cos(deg_to_rad(cub->var->ca));
	cub->var->line_h = 40000 / (cub->var->dis_h);
	cub->var->wall->ty_step = texture_(cub)->height
		/ (float)cub->var->line_h;
	cub->var->line_off = 600 - (cub->var->line_h / 2);
	t1.x_p = (cub->var->r);
	t1.y_p = cub->var->line_off;
	t2.x_p = cub->var->r;
	t2.y_p = cub->var->line_off + cub->var->line_h;
	draw_sky_floor(cub, t1, t2);
	put_textured_wall(t1, t2, cub);
}
