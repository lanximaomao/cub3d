
#include "cub3D.h"
// direction
static void matrix_assignment(t_cub *cub, char **tmp_matrix)
{
	int i;
	int j;

	i = 0;
	printf("y=%d, x=%d\n", cub->input->map->size_x, cub->input->map->size_y);
	printf("matrix_1d=\n%s\n",  cub->input->map->map_1d);
	cub->input->map->size_y--;
	while (i < cub->input->map->size_y)
	{
		printf("line%d=%s\n", i, tmp_matrix[i]);
		j = 0;
		while (j < cub->input->map->size_x)
		{
			printf("i=%d, j=%d\n", i, j);
			if (j >= (int)ft_strlen(tmp_matrix[i]))
				cub->input->map->matrix[i][j] = '*';
			else if (tmp_matrix[i][j] == ' ' || tmp_matrix[i][j] == '0')
				cub->input->map->matrix[i][j] = '_';
			else
				cub->input->map->matrix[i][j] = tmp_matrix[i][j];
			j++;
		}
		i++;
	}
	printf("\n\nbefore validation check");
	display_map(cub->input->map->matrix);
	if (valid_map(cub) == -1)
		ft_exit("invalid map", 3);
	printf("\n\nafter validation check");
	display_map(cub->input->map->matrix);
}

int get_matrix(t_cub *cub)
{
	int i;
	char **tmp_matrix;

	i = 0;
	if (!ft_strncmp(cub->input->map->map_1d, "", 1))
		ft_exit("map missing", 3);
	if (valid_char(cub->input->map->map_1d) == -1)
		ft_exit("map with invalid characters", 3);
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
	//display_map(cub->input->map->matrix);
	display_texture(cub->input);
	display_color(cub->input);
	return (0);
}

static int	get_map_x(char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0' && str[len] != '\n')
		len++;
	return (len);
}

int get_map(t_cub *cub, char* line, int *nl_flag)
{
	if (cub->input->count != 6) // check out whether at this point all the necessary parameters are passed.
		ft_exit ("map error", 3); // map error
	if ((int)ft_strlen(line) > cub->input->map->size_x) // calculate size_x of map
		cub->input->map->size_x = get_map_x(line);
	if (line[0] == '\n')
		(*nl_flag)++;
	if (*nl_flag > 1)
		ft_exit("nl inside map", 3);//?
	cub->input->map->size_y += 1; 	// calculate size_y of the map
	cub->input->map->map_1d = ft_strjoin_gnl(cub->input->map->map_1d, line); // if null
	if (!cub->input->map->map_1d)
		ft_exit("malloc fail", 1);
	return (0);
}

