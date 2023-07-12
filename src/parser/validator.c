/*
** 1. only contains 6 possible characters, 0, 1, N, S, E, W
** 2. closed/surrounded by walls
** 3. if one more , at the end of the color code?
*/

// if no player is present, is it a good map? see test_map

#include "cub3D.h"

int valid_char(char* str)
{
	int i;
	int player_flag;

	i = 0;
	player_flag = 0;
	while (str[i])
	{
		printf("%c", str[i]);
		if (str[i] != '\n' && str[i] != '0' && str[i] != '1' &&  str[i] != ' ')
		{
			if (str[i] == 'N' || str[i] == 'S' || str[i] == 'W'|| str[i] == 'E' )
				player_flag++;
			else
				return (-1);
		}
		i++;
	}
	if (player_flag != 1)
		return (-1);
	return (0);
}

// change every possible '_' to '*'
void flood_fill_star(t_cub *cub, int row, int col, char old, char new)
{
	// breaking condition?
	if ( col >= cub->input->map->size_x
		|| row >= cub->input->map->size_y
		|| col < 0 || row < 0
		|| cub->input->map->matrix[row][col] == new )
		return;
	else
	{
		if (cub->input->map->matrix[row][col] == old)
			cub->input->map->matrix[row][col] = new;
		flood_fill_star(cub, row, col+1, old, new);
		flood_fill_star(cub, row, col-1, old, new);
		flood_fill_star(cub, row + 1, col, old, new);
		flood_fill_star(cub, row - 1, col, old, new);
	}
}

int valid_map(t_cub *cub)
{
	// flood fill "_" next to *

	flood_fill_star(cub, 0, 0, cub->input->map->matrix[0][0], cub->input->map->matrix[0][0] + 1);

	// flood fill "_" with x
	return(0);
}
