#include "cub3D.h"

static int	get_map_col(char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0' && str[len] != '\n')
		len++;
	return (len + 2);
}

int	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\n' && str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

/*
** check out whether at this point all the necessary parameters are passed.
*/
int	get_map(t_cub *cub, char *line, int *nl_flag)
{
	if (cub->input->count != 6)
		ft_exit("map error", 3);
	if ((int)ft_strlen(line) > cub->input->map->size_x)
		cub->input->map->size_x = get_map_col(line);
	if (*nl_flag == 0 && is_empty(line))
		(*nl_flag) = 1;
	if (*nl_flag == 1 && is_empty(line) == 0)
		ft_exit("Error: multiple nl inside map", 3);
	if (*nl_flag == 0)
		cub->input->map->map_1d = ft_strjoin_gnl(cub->input->map->map_1d, line);
	if (!cub->input->map->map_1d)
		ft_exit("Error: malloc fail", 1);
	return (0);
}
