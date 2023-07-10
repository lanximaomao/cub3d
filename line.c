/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:56:52 by lsun              #+#    #+#             */
/*   Updated: 2023/07/10 13:09:58 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "render.h"

static int	ft_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

static t_line	line_init(t_pos pos0, t_pos pos1)
{
	t_line	line;

	line.dx = ft_abs(pos1.x - pos0.x);
	if (pos0.x < pos1.x)
		line.sx = 1;
	else
		line.sx = -1;
	line.dy = -ft_abs(pos1.y - pos0.y);
	if (pos0.y < pos1.y)
		line.sy = 1;
	else
		line.sy = -1;
	line.err = line.dx + line.dy;
	line.e2 = 2 * line.err;
	return (line);
}

int	bresenham_line(t_pos pos0, t_pos pos1, t_cub *cub)
{
	t_line	line;

	line = line_init(pos0, pos1);
	while (1)
	{
		pixel_color(cub, pos0.x, pos0.y, WHITE);
		if (pos0.x == pos1.x && pos0.y == pos1.y)
			break ;
		line.e2 = 2 * line.err;
		if (line.e2 >= line.dy)
		{
			line.err += line.dy;
			pos0.x += line.sx;
		}
		if (line.e2 <= line.dx)
		{
			line.err += line.dx;
			pos0.y += line.sy;
		}
	}
	return (1);
}
