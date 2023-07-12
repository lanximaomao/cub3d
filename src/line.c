/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:56:52 by lsun              #+#    #+#             */
/*   Updated: 2023/07/10 14:28:39 by asarikha         ###   ########.fr       */
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

int	bresenham_line(t_position pos0, t_position pos1, t_cub *cub)
{
	t_line	line;

	line = line_init(pos0, pos1);
	while (1)
	{
		pixel_color(cub, pos0.x_p, pos0.y_p, PURPLE);
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
