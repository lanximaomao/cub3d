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
			else if (tmp_matrix[i - 1][j - 1] == ' '
				|| tmp_matrix[i - 1][j - 1] == '0')
				cub->input->map->matrix[i][j] = '_';
			else
				cub->input->map->matrix[i][j] = tmp_matrix[i - 1][j - 1];
		}
	}
	free_char(tmp_matrix);
	if (valid_map(cub) == -1)
		ft_exit("Error: invalid map", 3);
}

static int	get_map_row(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			count++;
		}
		i++;
	}
	return (count + 2);
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
		ft_exit("Error: map missing", 3);
	if (valid_char(cub->input->map->map_1d) == -1)
		ft_exit("Error: map with invalid characters", 3);
	cub->input->map->size_y = get_map_row(cub->input->map->map_1d);
	tmp_matrix = ft_split(cub->input->map->map_1d, '\n');
	if (!tmp_matrix)
		ft_exit("malloc fail", 1);
	cub->input->map->matrix = ft_calloc(sizeof(char *), cub->input->map->size_y
			+ 1);
	cub->input->map->matrix[cub->input->map->size_y] = NULL;
	while (++i < cub->input->map->size_y)
	{
		cub->input->map->matrix[i] = ft_calloc(sizeof(char),
				cub->input->map->size_x + 1);
		if (!cub->input->map->matrix[i])
			ft_exit("malloc fail", 1);
		cub->input->map->matrix[i][cub->input->map->size_x] = '\0';
	}
	matrix_assignment(cub, tmp_matrix);
	return (0);
}
