#include "cub3D.h"

int	free_char(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (1);
	while (str[i] != NULL)
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
	return (1);
}

int	free_str(char *str)
{
	free(str);
	str = NULL;
	return (1);
}

void	ft_exit(char *msg, int exit_code)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(exit_code);
}

int	free_everything(t_cub *cub)
{
	free_str(cub->input->map->map_1d);
	free_char(cub->input->map->matrix);
	free(cub->input->color_f);
	free(cub->input->color_c);
	free_str(cub->input->t_east);
	free_str(cub->input->t_west);
	free_str(cub->input->t_south);
	free_str(cub->input->t_north);
	free(cub->input->map);
	free(cub->input->position);
	free(cub->var->wall);
	free(cub->var);
	free(cub->input);
	free(cub->key);
	free_tex(cub);
	return (1);
}
