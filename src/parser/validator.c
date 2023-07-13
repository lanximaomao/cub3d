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
	//if (player_flag != 1) // turn on after debugging
	//	return (-1);
	return (0);
}

static int find_walls(t_cub *cub, int *i, int *j)
{
	int row;
	int col;

	row = 0;
	while (row < cub->input->map->size_y)
	{
		col = 0;
		while (col < cub->input->map->size_x)
		{
			if (cub->input->map->matrix[row][col] == '1')
			{
				*i = row;
				*j = col;
				printf("I found a wall at [%d][%d]\n", *i, *j);
				return (-1);
			}
			col++;
		}
		row++;
	}
	return (1);
}

// change every possible '_' to '*'
void flood_fill(t_cub *cub, int row, int col, char old, char new)
{
	// breaking condition?
	if (row >= cub->input->map->size_y
		|| col >= cub->input->map->size_x
		|| col < 0 || row < 0
		|| cub->input->map->matrix[row][col] != old)
		return;
	else
	{
		cub->input->map->matrix[row][col] = new;
		flood_fill(cub, row, col+1, old, new);
		flood_fill(cub, row, col-1, old, new);
		flood_fill(cub, row + 1, col, old, new);
		flood_fill(cub, row - 1, col, old, new);
	}
	display_map(cub->input->map->matrix);
}

int valid_map(t_cub *cub)
{
	int row;
	int col;
	int count;

	row = 0;
	col = 0;
	count = 0;
	while (find_walls(cub, &row, &col) == -1) // find where wall is
	{
		printf("find out wall at row %d and col %d\n", row, col);
		if (row < cub->input->map->size_y && col < cub->input->map->size_x)
		{
			flood_fill(cub, row, col, cub->input->map->matrix[row][col], 'x' + count); // starting point is a '1'
			count++;
		}
		else
			printf("no more walls\n");
	}
	// count how many island
	return(0);
}
