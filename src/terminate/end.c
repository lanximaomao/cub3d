#include "cub3D.h"

void	clean_exit(int exit_code, t_cub *cub3d)
{
	if (!cub3d)
		exit(exit_code);
	if (cub3d->img->img_ptr && cub3d->win_ptr && cub3d->mlx_ptr)
	{
		mlx_destroy_image(cub3d->mlx_ptr, cub3d->img->img_ptr);
		mlx_destroy_window(cub3d->mlx_ptr, cub3d->win_ptr);
		cub3d->mlx_ptr = NULL;
		cub3d->win_ptr = NULL;
		cub3d->img->addr = NULL;
		exit (exit_code);
	}
	else if (cub3d->win_ptr && cub3d->mlx_ptr)
	{
		mlx_destroy_window(cub3d->mlx_ptr, cub3d->win_ptr);
		cub3d->win_ptr = NULL;
		cub3d->mlx_ptr = NULL;
		exit (exit_code);
	}
	else if (cub3d->img->img_ptr && cub3d->mlx_ptr)
	{
		mlx_destroy_image(cub3d->mlx_ptr, cub3d->img->img_ptr);
		cub3d->img->img_ptr = NULL;
		exit (exit_code);
	}
	exit (exit_code);
}

int	message(char *str1, char *str2, int errno)
{
	ft_putstr_fd("cub3d: ", 2);
	ft_putstr_fd(str1, 2);
	ft_putendl_fd(str2, 2);
	return (errno);
}

static void	free_tex_matrix(int **matrix, int height, int width)
{
	int		i;

	i = 0;
	if (!matrix)
		return ;
	while (i < width)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	free_tex(t_cub *cub)
{
	free(cub->tex_e->type);
	free(cub->tex_w->type);
	free(cub->tex_s->type);
	free(cub->tex_n->type);
	free_tex_matrix(cub->tex_e->matrix, cub->tex_e->height, cub->tex_e->width);
	free_tex_matrix(cub->tex_w->matrix, cub->tex_w->height, cub->tex_w->width);
	free_tex_matrix(cub->tex_s->matrix, cub->tex_s->height, cub->tex_s->width);
	free_tex_matrix(cub->tex_n->matrix, cub->tex_n->height, cub->tex_n->width);
	free(cub->tex_e);
	free(cub->tex_w);
	free(cub->tex_s);
	free(cub->tex_n);
}

int	end_cub3d(t_cub *cub3d)
{
	//free_everything and close fds
	free_everything(cub3d);
	clean_exit(0, cub3d);
	return (0);
}
