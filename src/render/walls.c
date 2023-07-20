#include "cub3D.h"

unsigned long	calculate_hex_color(t_color_rgb *rgb)
{
	return ((rgb->r & 0xff) << 16)
		+ ((rgb->g & 0xff) << 8) + (rgb->b & 0xff);
}

void	draw_sky_floor(t_cub *cub, t_position	t1, t_position	t2)
{
	t_position		s1;
	t_position		s2;
	t_position		f1;
	t_position		f2;

	s1.x_p = t1.x_p;
	s2.x_p = t1.x_p;
	s1.y_p = 0;
	s2.y_p = t1.y_p - 1;
	if (t1.x_p < GRID_P * cub->input->map->size_x
		&& s2.y_p < GRID_P * cub->input->map->size_y)
			s2.y_p = 0;
	if (t1.x_p < GRID_P * cub->input->map->size_x
		&& s2.y_p >= GRID_P * cub->input->map->size_y)
			s1.y_p = GRID_P * cub->input->map->size_y + 1;
	bresenham_line (s1, s2, cub, calculate_hex_color(cub->input->color_c));
	f1.x_p = t1.x_p;
	f2.x_p = t1.x_p;
	f1.y_p = t2.y_p + 1;
	f2.y_p = WIN_SIZE_Y - 1;
	if (t1.x_p < GRID_P * cub->input->map->size_x
		&& f1.y_p <= GRID_P * cub->input->map->size_y)
			f1.y_p = GRID_P * cub->input->map->size_y + 1;
	bresenham_line (f1, f2, cub, calculate_hex_color(cub->input->color_f));
	return ;
}

void	new_tex(t_cub *cub, t_tex *tex, char *file, char *type)
{
	tex->img->img_ptr = mlx_xpm_file_to_image(cub->mlx_ptr, file,
			&(tex->width), &(tex->height));
	if (!tex->img->img_ptr)
		clean_exit(message("MLX: error copenning xpm file.", "", 1), cub);
	tex->img->addr
		= mlx_get_data_addr(tex->img->img_ptr, &(tex->img->bpp),
			&(tex->img->size_line), &(tex->img->endian));
	if (!tex->img->addr)
		clean_exit(message("MLX: error getting data address.", "", 1), cub);
		tex->type = ft_strdup(type); // to be freed

}

void	init_tex(t_cub *cub)
{
	cub->tex_e = ft_calloc(sizeof(t_tex), 1);
	if (!(cub->tex_e))
		end_cub(cub);
	cub->tex_w = ft_calloc(sizeof(t_tex), 1);
	if (!(cub->tex_w))
		end_cub(cub);
	cub->tex_n = ft_calloc(sizeof(t_tex), 1);
	if (!(cub->tex_n))
		end_cub(cub);
	cub->tex_s = ft_calloc(sizeof(t_tex), 1);
	if (!(cub->tex_s))
		end_cub(cub);
	cub->tex_e->img = ft_calloc(sizeof(t_img), 1);
	if (!(cub->tex_e->img))
		end_cub(cub);
	cub->tex_w->img = ft_calloc(sizeof(t_img), 1);
	if (!(cub->tex_w->img))
		end_cub(cub);
	cub->tex_n->img = ft_calloc(sizeof(t_img), 1);
	if (!(cub->tex_n->img))
		end_cub(cub);
	cub->tex_s->img = ft_calloc(sizeof(t_img), 1);
	if (!(cub->tex_s->img))
		end_cub(cub);
	new_tex(cub, cub->tex_e, cub->input->t_east, "EA");
	new_tex(cub, cub->tex_w, cub->input->t_west, "WE");
	new_tex(cub, cub->tex_n, cub->input->t_north, "NO");
	new_tex(cub, cub->tex_s, cub->input->t_south, "SO");
}

void	draw_walls(t_cub *cub)
{
	t_position	t1;
	t_position	t2;
	int			i;

	cub->var->ca = fix_ang(cub->var->pa - cub->var->ra);
	cub->var->dis_h = cub->var->dis_h * cos(deg_to_rad(cub->var->ca));
	cub->var->line_h = 40000 / (cub->var->dis_h);
	if (cub->var->line_h > 1200)
		cub->var->line_h = 1200;
	cub->var->line_off = 600 - (cub->var->line_h / 2);
	t1.x_p = (cub->var->r) * 2;
	t1.y_p = cub->var->line_off;
	t2.x_p = cub->var->r * 2;
	t2.y_p = cub->var->line_off + cub->var->line_h;
	i = -1;
	while (++i < 2)
	{
		draw_sky_floor(cub, t1, t2);
		if (t1.x_p < GRID_P * cub->input->map->size_x
			&& t1.y_p < GRID_P * cub->input->map->size_y)
			t1.y_p = GRID_P * cub->input->map->size_y;
		bresenham_line (t1, t2, cub, YELLOW);
		//put_texture_to_wall(cub)
		t1.x_p++;
		t2.x_p++;
	}
}
