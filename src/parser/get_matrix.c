#include "cub3D.h"

/*
** display_map("before validation", cub->input->map->matrix);
** display_map("after validation", cub->input->map->matrix);
*/
static void	matrix_assignment(t_cub *cub, char **tmp_matrix)
{
	int	i;
	int	j;

	i = -1;
	while (++i < cub->input->map->size_y)
	{
		j = -1;
		while (++j < cub->input->map->size_x)
		{
			if (i == 0 || i == cub->input->map->size_y - 1 || j == 0
				|| j == cub->input->map->size_x - 1)
				cub->input->map->matrix[i][j] = '_';
			else if (j > (int)ft_strlen(tmp_matrix[i - 1]))
				cub->input->map->matrix[i][j] = '_';
			else if (tmp_matrix[i - 1][j - 1] == ' ')
				cub->input->map->matrix[i][j] = '_';
			else if (tmp_matrix[i - 1][j - 1] == '0')
				cub->input->map->matrix[i][j] = '0';
			else
				cub->input->map->matrix[i][j] = tmp_matrix[i - 1][j - 1];
		}
	}
	free_char(tmp_matrix);
	valid_map(cub);
	matrix_revert(cub);;
}

static int	get_map_row(char *str)
{
	int	i;
	int	row;

	i = 0;
	row = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			row++;
		i++;
	}
	return (row + 2);
}

static int	get_map_col(char *str)
{
	int	col;
	int	tmp_col;

	col = 0;
	tmp_col = 0;
	while (*str != '\0')
	{
		tmp_col = 0;
		while (*str != '\n')
		{
			tmp_col++;
			str++;
		}
		str++;
		if (tmp_col > col)
			col = tmp_col;
	}
	return (col + 2);
}

static int	get_map_size(t_cub *cub)
{
	cub->input->map->size_x = get_map_col(cub->input->map->map_1d);
	cub->input->map->size_y = get_map_row(cub->input->map->map_1d);
	return (1);
}

/*
** tmp_matrix to be freed
*/
int	get_matrix(t_cub *cub)
{
	int		i;
	char	**tmp_matrix;

	i = -1;
	if (!ft_strncmp(cub->input->map->map_1d, "", 1))
		ft_exit("Error\n-----> map missing", 3);
	if (valid_char(cub->input->map->map_1d) == -1)
		ft_exit("Error\n-----> map with invalid characters", 3);
	get_map_size(cub);
	tmp_matrix = ft_split(cub->input->map->map_1d, '\n');
	if (!tmp_matrix)
		ft_exit("malloc fail", 1);
	cub->input->map->matrix = ft_calloc(sizeof(char *),
			cub->input->map->size_y + 1);
	cub->input->map->matrix[cub->input->map->size_y] = NULL;
	while (++i < cub->input->map->size_y)
	{
		cub->input->map->matrix[i] = malloc(cub->input->map->size_x + 1);
		if (!cub->input->map->matrix[i])
			ft_exit("malloc fail", 1);
		cub->input->map->matrix[i][cub->input->map->size_x] = '\0';
	}
	matrix_assignment(cub, tmp_matrix);
	return (0);
}
