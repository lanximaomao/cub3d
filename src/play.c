#include "cub3D.h"

// x and y are the coordinates in pixels
void	my_mlx_pixel_put(t_img *img, int x, int y, int color_code)
{
	int	dst;

	dst = y * (img->size_line / 4) + x;
	if ((x >= 0 && x < 400) && (y >= 0 && y < 400))
		img->addr[dst] = color_code;
}

// size_len = how many bytes per line, that is 4 bytes per piexel * window_width
// bbp = how many bits per pixel, that is 4 (bytes per pixel) times (8 bites per pixel).

int	close_window(t_tex *tex)
{
	exit (1);
}

int	deal_key(int keycode, t_tex *tex)
{
	if (keycode == 53)
	{
		//mlx_destroy_window(tex->mlx_ptr, tex->win->ptr);
		exit(1);
	}
	return (0);
}
int	main(void)
{
	int i = 0;
	int j = 0;
	t_tex	*tex;
	void	*mlx_ptr;
	void	*win_ptr;
	char *filename;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 400, 400, "test");

	tex = malloc(sizeof(t_tex));
	if (!tex)
		exit(1);
	tex->img = malloc(sizeof(t_img));

	tex->height = 64;
	tex->width = 64;

	tex->img->img_ptr = mlx_xpm_file_to_image(mlx_ptr,
		"./textures/simonkraft/basalt_top.xpm", &tex->width, &tex->height); // 64 * 64
	tex->img->addr = mlx_get_data_addr(tex->img->img_ptr, &tex->img->bpp, &tex->img->size_line,
		&tex->img->endian);

	while(64*i < 400)
	{
		j = 0;
		while (64*j < 400)
		{
			mlx_put_image_to_window(mlx_ptr, win_ptr, tex->img->img_ptr, 64*i, 64*j);
			j++;
		}
		i++;
	}
	mlx_hook(win_ptr, 2, 0, deal_key, tex);
	mlx_hook(win_ptr, 17, 0, close_window, tex);
	mlx_loop(mlx_ptr);
	return (0);
}
