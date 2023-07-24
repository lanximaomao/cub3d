#include "cub3D.h"

void	fill_tex_matrix(t_tex *tex)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < tex->height)
	{
		x = 0;
		while (x < tex->width)
		{
			tex->matrix[y][x] = *(unsigned int*)(tex->img->addr +  (tex->line_length * y) + (x * (tex->bpp / 8)));
			//tex->matrix[y][x] = (int)tex->img->addr[tex->width * y + x];
			x++;
		}
		printf("\n");
		y++;
	}
	printf("\n\n\n");
}

void	get_tex(t_cub *cub3d, t_tex *tex, char *file, char *type)
{
	int	i;

	tex->img->img_ptr = mlx_xpm_file_to_image(cub3d->mlx_ptr, file,
			&(tex->width), &(tex->height));
	if (!tex->img->img_ptr)
		clean_exit(message("MLX: error openning xpm file.", "", 1), cub3d);
	tex->img->addr
		= mlx_get_data_addr(tex->img->img_ptr, &(tex->bpp),
			&(tex->line_length), &(tex->endian));
	if (!tex->img->addr)
		clean_exit(message("MLX: error getting data address.", "", 1), cub3d);
	tex->type = ft_strdup(type); // to be freed
	tex->matrix = ft_calloc(sizeof(int *) * tex->height, 1);
	if (!tex->matrix)
		end_cub3d(cub3d);
	i = -1;
	while (++i < tex->height)
	{
		tex->matrix[i] = ft_calloc(sizeof(int) * tex->width, 1);
		if (!tex->matrix[i])
			end_cub3d(cub3d);

	}
	fill_tex_matrix(tex);
}



void	alocate_tex(t_cub *cub3d)
{
	cub3d->tex_e = ft_calloc(sizeof(t_tex), 1);
	if (!(cub3d->tex_e))
		end_cub3d(cub3d);
	cub3d->tex_w = ft_calloc(sizeof(t_tex), 1);
	if (!(cub3d->tex_w))
		end_cub3d(cub3d);
	cub3d->tex_n = ft_calloc(sizeof(t_tex), 1);
	if (!(cub3d->tex_n))
		end_cub3d(cub3d);
	cub3d->tex_s = ft_calloc(sizeof(t_tex), 1);
	if (!(cub3d->tex_s))
		end_cub3d(cub3d);
	cub3d->tex_e->img = ft_calloc(sizeof(t_img), 1);
	if (!(cub3d->tex_e->img))
		end_cub3d(cub3d);
	cub3d->tex_w->img = ft_calloc(sizeof(t_img), 1);
	if (!(cub3d->tex_w->img))
		end_cub3d(cub3d);
	cub3d->tex_n->img = ft_calloc(sizeof(t_img), 1);
	if (!(cub3d->tex_n->img))
		end_cub3d(cub3d);
	cub3d->tex_s->img = ft_calloc(sizeof(t_img), 1);
	if (!(cub3d->tex_s->img))
		end_cub3d(cub3d);
}

void	texture_extension_check(t_cub *cub3d)
{
	int	str_end;

	str_end = ft_strlen(cub3d->input->t_east);
	str_end = str_end - 4;
	if (ft_strncmp(&(cub3d->input->t_east[str_end]), ".xpm", 4))
		clean_exit(message("error textures was not in .xpm.", "", 1),
			cub3d);
	str_end = ft_strlen(cub3d->input->t_west);
	str_end = str_end - 4;
	if (ft_strncmp(&(cub3d->input->t_west[str_end]), ".xpm", 4))
		clean_exit(message("error textures was not in .xpm.", "", 1),
			cub3d);
	str_end = ft_strlen(cub3d->input->t_north);
	str_end = str_end - 4;
	if (ft_strncmp(&(cub3d->input->t_north[str_end]), ".xpm", 4))
		clean_exit(message("error textures was not in .xpm.", "", 1),
			cub3d);
	str_end = ft_strlen(cub3d->input->t_south);
	str_end = str_end - 4;
	if (ft_strncmp(&(cub3d->input->t_south[str_end]), ".xpm", 4))
		clean_exit(message("error textures was not in .xpm.", "", 1),
			cub3d);
}

void	init_tex(t_cub *cub3d)
{
	texture_extension_check(cub3d);
	alocate_tex(cub3d);
	get_tex(cub3d, cub3d->tex_e, cub3d->input->t_east, "EA");
	get_tex(cub3d, cub3d->tex_w, cub3d->input->t_west, "WE");
	get_tex(cub3d, cub3d->tex_n, cub3d->input->t_north, "NO");
	get_tex(cub3d, cub3d->tex_s, cub3d->input->t_south, "SO");
	if (cub3d->tex_e->img)
		mlx_destroy_image(cub3d->mlx_ptr, cub3d->tex_e->img);
	if (cub3d->tex_s->img)
		mlx_destroy_image(cub3d->mlx_ptr, cub3d->tex_s->img);
	if (cub3d->tex_n->img)
		mlx_destroy_image(cub3d->mlx_ptr, cub3d->tex_n->img);
	if (cub3d->tex_w->img)
		mlx_destroy_image(cub3d->mlx_ptr, cub3d->tex_w->img);
}
