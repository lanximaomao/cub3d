/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:18:48 by lsun              #+#    #+#             */
/*   Updated: 2023/07/31 15:18:49 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float	fix_ang(float a)
{
	if (a > 359)
	{
		a -= 360;
	}
	if (a < 0)
	{
		a += 360;
	}
	return (a);
}

float	deg_to_rad(float a)
{
	return (a * M_PI / 180.0);
}

int	ft_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

unsigned long	calculate_hex_color(t_color_rgb *rgb)
{
	return (((rgb->r & 0xff) << 16)
		+ ((rgb->g & 0xff) << 8) + (rgb->b & 0xff));
}
