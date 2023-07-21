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

static void	free_double_pointer(void **pointer, int size)
{
	int		i;

	i = 0;
	if (!pointer)
		return ;
	while (i <= size)
	{
		free(pointer[i]);
		i++;
	}
	free(pointer);
}

int	free_parsing(t_cub *cub)
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
	free(cub->var);
	free(cub->input);
	free(cub->key);
	//free(cub->tex_e);
	//free(cub->tex_w);
	//free(cub->tex_s);
	//free(cub->tex_n);
	//free(cub->tex_e->img);
	//free(cub->tex_w->img);
	//free(cub->tex_s->img);
	//free(cub->tex_n->img);
	free(cub->tex_e->type);
	free(cub->tex_w->type);
	free(cub->tex_s->type);
	free(cub->tex_n->type);
	free_double_pointer((void **)cub->tex_e->matrix, cub->tex_e->height);
	return (1);
}
