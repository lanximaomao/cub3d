#include "cub3D.h"

int	find_zero(t_cub *cub, int *row, int *col, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < cub->input->map->size_y)
	{
		j = 0;
		while (j < cub->input->map->size_x)
		{
			if (cub->input->map->matrix[i][j] == c)
			{
				*row = i;
				*col = j;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (-1);
}

char	which_dir(t_cub *cub)
{
	char	direction;

	direction = 0;
	if (cub->input->map->direction == 0)
		direction = 'E';
	else if (cub->input->map->direction == 90)
		direction = 'N';
	else if (cub->input->map->direction == 180)
		direction = 'W';
	else if (cub->input->map->direction == 270)
		direction = 'S';
	return (direction);
}
