/*
** 1. only contains 6 possible characters, 0, 1, N, S, E, W
** 2. closed/surrounded by walls
** 3. if one more , at the end of the color code?
*/

// if no player is present, is it a good map? see test_map

#include "cub3D.h"

int valid_filetype(char *str)
{
	char *ret;

	ret = ft_strnstr(str, ".cub", ft_strlen(str));
	if (!ret)
		return (-1);
	if (*(ret+4) != '\0') // filename has to end with .cub
		return(-1);
	return (1);
}

int valid_char(char * str)
{
	int i;
	int player_flag;

	i = 0;
	player_flag = 0;
	while (str[i])
	{
		//printf("%c", str[i]);
		if (str[i] != '\n' && str[i] != '0' && str[i] != '1' &&  str[i] != ' ')
		{
			if (str[i] == 'N' || str[i] == 'S' || str[i] == 'W'|| str[i] == 'E' )
				player_flag++;
			else
				ft_exit("invalid chars", 3);
		}
		i++;
	}
	if (player_flag != 1) // turn on after debugging
		ft_exit("player error", 3);
	return (0);
}

static void check_down(t_cub *cub, int row, int col, char c, int *boundry_check)
{
	while (row < cub->input->map->size_y)
	{
		if (cub->input->map->matrix[row][col] == c)
		{
			(*boundry_check)++;
			break;
		}
		row++;
	}
}

static void check_up(t_cub *cub, int row, int col, char c, int *boundry_check)
{
	while (row >= 0)
	{
		if (cub->input->map->matrix[row][col] == c)
		{
			(*boundry_check)++;
			break;
		}
		row--;
	}
}

static void check_left(t_cub *cub, int row, int col, char c, int *boundry_check)
{

	while (col >= 0)
	{
		if (cub->input->map->matrix[row][col] == c)
		{
			(*boundry_check)++;
			break;
		}
		col--;
	}
}

static void check_right(t_cub *cub, int row, int col, char c, int *boundry_check)
{
	while (col < cub->input->map->size_x)
	{
		if (cub->input->map->matrix[row][col] == c)
		{
			(*boundry_check)++;
			break;
		}
		col++;
	}
}

static int is_inland(t_cub *cub, int row, int col, char c)
{
	int boundry_check;

	boundry_check = 0;
	check_up(cub, row, col, c, &boundry_check);
	check_down(cub, row, col, c, &boundry_check);
	check_left(cub, row, col, c, &boundry_check);
	check_right(cub, row, col, c, &boundry_check);
	if (boundry_check == 4)
		return (1);
	else
		return (-1);
}

// add functionality here to flood only the walls are outside the island
static int find_island(t_cub *cub, int *i, int *j, char c, int *flag)
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
				// if it is inside another island
				if (*flag == 0) // not inland
				{
					*flag = 1;
					*i = row;
					*j = col;
					printf("I found a wall at [%d][%d]\n", *i, *j);
					return (-1);
				}
				else if (*flag == 1)
				{
					if (is_inland(cub, row, col, c) == -1) // not inland
						ft_exit("more than one islands", 3);
				}
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
	//display_map(cub->input->map->matrix);
}

int valid_map(t_cub *cub)
{
	int row;
	int col;
	int count;
	char c;
	int flag;

	row = 0;
	col = 0;
	count = 0;
	c = 'x';
	flag = 0;
	while (find_island(cub, &row, &col, c, &flag) == -1) // find where wall is
	{
		printf("find out wall at row %d and col %d\n", row, col);
		if (row < cub->input->map->size_y && col < cub->input->map->size_x)
		{
			flood_fill(cub, row, col, cub->input->map->matrix[row][col], c + count); // starting point is a '1'
			count++;
		}
		else
			printf("no more walls\n");
	}
	// count how many island
	return(0);
}
