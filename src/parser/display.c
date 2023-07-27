/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:31:11 by asarikha          #+#    #+#             */
/*   Updated: 2023/07/27 13:04:01 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	display_map(char *msg, char **matrix)
{
	int	i;
	int	j;

	i = 0;
	printf("\n\n%s\n\n", msg);
	while (matrix[i])
	{
		j = 0;
		while (matrix[i][j])
		{
			printf("%c", matrix[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	display_texture(t_input *input)
{
	printf("\n\nt_north=%s\n", input->t_north);
	printf("t_south=%s\n", input->t_south);
	printf("t_west=%s\n", input->t_west);
	printf("t_east=%s\n\n", input->t_east);
}

void	display_color(t_input *input)
{
	int	i;

	i = 0;
	printf("floor color = %d, %d, %d\n", input->color_f->r, input->color_f->g,
		input->color_f->b);
	printf("ceiling color = %d, %d, %d\n", input->color_c->r, input->color_c->g,
		input->color_c->b);
}
