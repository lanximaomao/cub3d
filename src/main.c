#include "cub3D.h"

void	hook_and_loop(t_cub *cub)
{
	mlx_hook(cub->win_ptr, EVENT_CLOSE_BTN, 0, end_cub, cub);
	//mlx_hook(cub->win_ptr, EVENT_KEY_RLEASE, 1L << 1, key_release, cub);
	mlx_hook(cub->win_ptr, EVENT_KEY_PRESS, 1L << 0, key_press, cub);
	//mlx_key_hook(cub->win_ptr, key_event, cub);
	//mlx_mouse_hook(cub->win_ptr, mouse_event, &cub);
	mlx_loop(cub->mlx_ptr);
}

// pa is player angle
void	clean_init_cub(t_cub *cub)
{
	cub->var->pa = cub->input->map->direction;
	cub->var->pdx = cos(deg_to_rad(cub->var->pa));
	cub->var->pdy = -sin(deg_to_rad(cub->var->pa));
	cub->mlx_ptr = mlx_init();
	if (!cub->mlx_ptr)
		clean_exit(message("MLX: error connecting to mlx.", "", 1), cub);
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, WIN_SIZE_X, WIN_SIZE_Y,
			"cub");
	if (!cub->win_ptr)
		clean_exit(message("MLX: error creating window.", "", 1), cub);
	cub->img->img_ptr = mlx_new_image(cub->mlx_ptr, WIN_SIZE_X, WIN_SIZE_Y);
	if (!(cub->img->img_ptr))
		clean_exit(message("image creation error.", "", 1), cub);
	init_tex(cub);
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
	clean_init_cub(&cub);
	render(&cub);
	hook_and_loop(&cub);
	return (0);
}
