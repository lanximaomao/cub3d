#include "cub3D.h"

void	hook_and_loop(t_cub *cub3d)
{
	mlx_hook(cub3d->win_ptr, EVENT_CLOSE_BTN, 0, end_cub3d, cub3d);
	mlx_hook(cub3d->win_ptr, EVENT_KEY_RLEASE, 1L << 1, key_release, cub3d);
	mlx_hook(cub3d->win_ptr, EVENT_KEY_PRESS, 1L << 0, key_press, cub3d);
	//mlx_key_hook(cub3d->win_ptr, key_event, cub3d);
	//mlx_mouse_hook(cub3d->win_ptr, mouse_event, &cub3d);
	mlx_loop(cub3d->mlx_ptr);
}

void	clean_init_cub3d(t_cub *cub3d)
{
	cub3d->mlx_ptr = NULL;
	cub3d->win_ptr = NULL;
	cub3d->var->pa = cub3d->input->map->direction;
	cub3d->var->pdx = cos(deg_to_rad(cub3d->var->pa));
	cub3d->var->pdy = -sin(deg_to_rad(cub3d->var->pa));
	cub3d->mlx_ptr = mlx_init();
	if (!cub3d->mlx_ptr)
		clean_exit(message("MLX: error connecting to mlx.", "", 1), cub3d);
	cub3d->win_ptr = mlx_new_window(cub3d->mlx_ptr, WIN_SIZE_X, WIN_SIZE_Y,
			"cub3d");
	if (!cub3d->win_ptr)
		clean_exit(message("MLX: error creating window.", "", 1), cub3d);
	cub3d->img->img_ptr = mlx_new_image(cub3d->mlx_ptr, WIN_SIZE_X, WIN_SIZE_Y);
	if (!(cub3d->img->img_ptr))
		clean_exit(message("image creation error.", "", 1), cub3d);
}

int	main(int argc, char **argv)
{
	t_cub	cub;
	int		fd;

	if (argc != 2)
		ft_exit("Error\n-----> wrong number of arguments", 1);
	if (valid_filetype(argv[1]) == -1)
		ft_exit("Error\n-----> wrong type of file", 3);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_exit("Error: cannot open file", 1);
	parser(fd, &cub);
	close(fd);
	display_map("map", cub.input->map->matrix);
	display_texture(cub.input);
	display_color(cub.input);
	free_parsing(&cub);
	//clean_init_cub3d(&cub);
	//render(&cub);
	//hook_and_loop(&cub);
	return (0);
}
