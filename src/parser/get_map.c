#include "cub3D.h"

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
		ft_exit("Error\n-----> not all arguments are in place", 3);
	if (*nl_flag == 0 && is_empty(line))
		(*nl_flag) = 1;
	if (*nl_flag == 1 && is_empty(line) == 0)
		ft_exit("Error\n-----> multiple nl inside map", 3);
	if (*nl_flag == 0)
		cub->input->map->map_1d = ft_strjoin_gnl(cub->input->map->map_1d, line);
	if (!cub->input->map->map_1d)
		ft_exit("Error\n-----> malloc fail", 1);
	return (0);
}
