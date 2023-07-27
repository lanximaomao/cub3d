/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/07/27 13:04:52 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	ft_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

static t_line	line_init(t_position pos0, t_position pos1)
{
	t_line	line;

	line.dx = ft_abs(pos1.x_p - pos0.x_p);
	if (pos0.x_p < pos1.x_p)
		line.sx = 1;
	else
		line.sx = -1;
	line.dy = -ft_abs(pos1.y_p - pos0.y_p);
	if (pos0.y_p < pos1.y_p)
		line.sy = 1;
	else
		line.sy = -1;
	line.err = line.dx + line.dy;
	line.e2 = 2 * line.err;
	return (line);
}

int	bresenham_line(t_position pos0, t_position pos1, t_cub *cub, int color)
{
	t_line	line;

	line = line_init(pos0, pos1);
	while (1)
	{
		pixel_color(cub, pos0.x_p, pos0.y_p, color);
		if (pos0.x_p == pos1.x_p && pos0.y_p == pos1.y_p)
			break ;
		line.e2 = 2 * line.err;
		if (line.e2 >= line.dy)
		{
			line.err += line.dy;
			pos0.x_p += line.sx;
		}
		if (line.e2 <= line.dx)
		{
			line.err += line.dx;
			pos0.y_p += line.sy;
		}
	}
	return (1);
}
