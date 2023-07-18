
#include "cub3D.h"
// direction
static void matrix_assignment(t_cub *cub, char **tmp_matrix)
{
	int i;
	int j;

	i = 0;
	//cub->input->map->size_y--; // what happened here?
	//printf("x=%d, y=%d\n", cub->input->map->size_x, cub->input->map->size_y);
	while (i < cub->input->map->size_y)
	{
		j = 0;
		while (j < cub->input->map->size_x)
		{
			//printf("i=%d, j =%d\n", i, j);
			if ( i == 0 || i == cub->input->map->size_y - 1
				|| j == 0 || j == cub->input->map->size_x - 1)
				cub->input->map->matrix[i][j] = '_';
			else if (j > (int)ft_strlen(tmp_matrix[i - 1]))
				cub->input->map->matrix[i][j] = '_';
			else if (tmp_matrix[i - 1][j - 1] == ' ' || tmp_matrix[i - 1][j - 1] == '0')
				cub->input->map->matrix[i][j] = '_';
			else
				cub->input->map->matrix[i][j] = tmp_matrix[i - 1][j - 1];
			j++;
		}
		i++;
	}
	display_map("before validation", cub->input->map->matrix);
	if (valid_map(cub) == -1)
		ft_exit("Error: invalid map", 3);
	display_map("after validation", cub->input->map->matrix);
}

static int get_map_row(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			count++;
			//if (!str[i + 1]) // no nl at the end of map
			//	count++;
		}
		i++;
	}
	return (count+2);
}

int get_matrix(t_cub *cub)
{
	int i;
	char **tmp_matrix;

	i = 0;
	if (!ft_strncmp(cub->input->map->map_1d, "", 1))
		ft_exit("Error: map missing", 3);
	if (valid_char(cub->input->map->map_1d) == -1)
		ft_exit("Error: map with invalid characters", 3);
	cub->input->map->size_y = get_map_row(cub->input->map->map_1d);
	//printf("y=%d\n", cub->input->map->size_y);
	tmp_matrix = ft_split(cub->input->map->map_1d, '\n'); // to be freed
	if (!tmp_matrix)
		exit(1);
	cub->input->map->matrix = ft_calloc(sizeof(char *), cub->input->map->size_y + 1);
	cub->input->map->matrix[cub->input->map->size_y] = NULL;
	while (i < cub->input->map->size_y)
	{
		cub->input->map->matrix[i] = ft_calloc(sizeof(char), cub->input->map->size_x + 1);
		if (!cub->input->map->matrix[i])
			exit(1);
		cub->input->map->matrix[i][cub->input->map->size_x] = '\0';
		i++;
	}
	matrix_assignment(cub, tmp_matrix);
	display_texture(cub->input);
	display_color(cub->input);
	return (0);
}

static int	get_map_col(char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0' && str[len] != '\n')
		len++;
	return (len+2);
}

int is_empty(char *str)
{
	int i;

	i = 0;
	while (str[i]) // space or nl
	{
		if (str[i] != '\n' && str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int get_map(t_cub *cub, char* line, int *nl_flag)
{
	//if (line[0] == '\n')
	//	write(1, "here\n", 5);
	if (cub->input->count != 6) // check out whether at this point all the necessary parameters are passed.
		ft_exit ("map error", 3); // map error
	if ((int)ft_strlen(line) > cub->input->map->size_x) // calculate size_x of map
		cub->input->map->size_x = get_map_col(line);
	if (*nl_flag == 0 && is_empty(line))
		(*nl_flag) = 1;
	if (*nl_flag == 1 && is_empty(line) == 0)
		ft_exit("Error: multiple nl inside map", 3);
	if (*nl_flag == 0)
		cub->input->map->map_1d = ft_strjoin_gnl(cub->input->map->map_1d, line); // if null
	if (!cub->input->map->map_1d)
		ft_exit("Error: malloc fail", 1);
	return (0);
}

