#include "cub3D.h"

void	clean_exit(int exit_code, t_cub *cub)
{
	if (!cub)
		exit(exit_code);
	if (cub->tex_e->img)
		mlx_destroy_image(cub->mlx_ptr, cub->tex_e->img);
	if (cub->tex_s->img)
		mlx_destroy_image(cub->mlx_ptr, cub->tex_s->img);
	if (cub->tex_n->img)
		mlx_destroy_image(cub->mlx_ptr, cub->tex_n->img);
	if (cub->tex_w->img)
		mlx_destroy_image(cub->mlx_ptr, cub->tex_w->img);
	if (cub->img->img_ptr && cub->win_ptr && cub->mlx_ptr)
	{
		mlx_destroy_image(cub->mlx_ptr, cub->img->img_ptr);
		mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
		cub->mlx_ptr = NULL;
		cub->win_ptr = NULL;
		cub->img->addr = NULL;
		exit (exit_code);
	}
	else if (cub->win_ptr && cub->mlx_ptr)
	{
		mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
		cub->win_ptr = NULL;
		cub->mlx_ptr = NULL;
		exit (exit_code);
	}
	else if (cub->img->img_ptr && cub->mlx_ptr)
	{
		mlx_destroy_image(cub->mlx_ptr, cub->img->img_ptr);
		cub->img->img_ptr = NULL;
		exit (exit_code);
	}
	exit (exit_code);
}

int	message(char *str1, char *str2, int errno)
{
	ft_putstr_fd("cub: ", 2);
	ft_putstr_fd(str1, 2);
	ft_putendl_fd(str2, 2);
	return (errno);
}

int	end_cub(t_cub *cub)
{
	//free_everything and close fds
	free_parsing(cub);
	clean_exit(0, cub);
	return (0);
}
