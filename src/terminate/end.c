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

int	end_cub3d(t_cub *cub3d)
{
	//free_everything and close fds
	free_parsing(cub3d);
	clean_exit(0, cub3d);
	return (0);
}
