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
	int	wall_flag;

	i = 0;
	player_flag = 0;
	wall_flag = 0;
	while (str[i])
	{
		if (str[i] == '1')
			wall_flag = 1;
		if (str[i] != '\n' && str[i] != '0' && str[i] != '1' &&  str[i] != ' ')
		{
			if (str[i] == 'N' || str[i] == 'S' || str[i] == 'W'|| str[i] == 'E' )
				player_flag++;
			else
				ft_exit("Error: invalid chars", 3);
		}
		i++;
	}
	if (player_flag != 1) // turn on after debugging
		ft_exit("Error: player error", 3);
	if (wall_flag == 0)
		ft_exit("Error: no wall?", 3);
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
				if (*flag == 0)
				{
					*flag = 1;
					*i = row;
					*j = col;
					return (-1);
				}
				else if (*flag == 1)
				{
					if (is_inland(cub, row, col,c) == -1)
					{
						display_map("invalid map: more than one islands", cub->input->map->matrix);
						ft_exit("Error: more than one islands", 3);
					}
				}
			}
			col++;
		}
		row++;
	}
	return (1);
}

void flood_fill(t_cub *cub, int row, int col, char old, char new)
{
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
}

int find_char (t_cub *cub, int *row, int *col, char c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < cub->input->map->size_y)
	{
		j = 0;
		while (j < cub->input->map->size_x)
		{
			if (cub->input->map->matrix[i][j] == c && is_inland(cub, i, j,'x') == 1)
			{
				*row = i;
				*col = j;
				return (1) ;
			}
			j++;
		}
		i++;
	}
	return (-1);
}

int is_legal_boundary (t_cub *cub, char c, char direction)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < cub->input->map->size_y)
	{
		j = 0;
		while (j < cub->input->map->size_x)
		{
			if ((i == 0 || i == cub->input->map->size_y - 1
				|| j == 0 || j == cub->input->map->size_x -1)
				&& (cub->input->map->matrix[i][j] == c
				|| cub->input->map->matrix[i][j] == direction))
			{
				return(-1);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int is_closed(t_cub *cub)
{
	int row;
	int col;
	char direction;

	row = 0; // is it necessary to init?
	col = 0;
	direction = 0;
	while (find_char (cub, &row, &col, '_') == 1) // within boundary
		flood_fill(cub, row, col, '_', '@');
	if (cub->input->map->direction == 0)
		direction = 'E';
	else if (cub->input->map->direction == 90)
		direction = 'N';
	else if (cub->input->map->direction == 180)
		direction = 'W';
	else if (cub->input->map->direction == 270)
		direction = 'S';
	row = 0;
	col = 0;
	if (find_char(cub, &row, &col, direction) == 1)
		flood_fill(cub, row, col, direction, '@');
	if (is_legal_boundary(cub, '@', direction) == -1)
	{
		display_map("flood filled my boundary", cub->input->map->matrix);
		ft_exit("Error: wall not closed", 3);
	}
	return (1);
}

int valid_map(t_cub *cub)
{
	int row;
	int col;
	int count;
	int flag;

	row = 0;
	col = 0;
	count = 0;
	flag = 0;
	while (find_island(cub, &row, &col, 'x', &flag) == -1) // find where wall is
	{
		printf("find out wall at row %d and col %d\n", row, col);
		if (row < cub->input->map->size_y && col < cub->input->map->size_x)
		{
			flood_fill(cub, row, col, cub->input->map->matrix[row][col], 'x' + count); // starting point is a '1'
			count++;
		}
	}
	row = 0;
	col = 0;
	if (is_closed(cub) == -1 || !(get_direction(cub, &row, &col)
		&& is_inland(cub, row, col, 'x')))
		ft_exit("Error: wall not close", 3);
	return(0);
}
