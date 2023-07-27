#include "cub3D.h"

unsigned long	calculate_hex_color(t_color_rgb *rgb)
{
	return ((rgb->r & 0xff) << 16)
		+ ((rgb->g & 0xff) << 8) + (rgb->b & 0xff);
}

void	draw_sky_floor(t_cub *cub3d, t_position	t1, t_position	t2)
{
	t_position		s1;
	t_position		s2;
	t_position		f1;
	t_position		f2;

	s1.x_p = t1.x_p;
	s2.x_p = t1.x_p;
	s1.y_p = 0;
	s2.y_p = t1.y_p - 1;
	if (t1.x_p < GRID_P * cub3d->input->map->size_x
		&& s2.y_p < GRID_P * cub3d->input->map->size_y)
			s2.y_p = 0;
	if (t1.x_p < GRID_P * cub3d->input->map->size_x
		&& s2.y_p >= GRID_P * cub3d->input->map->size_y)
			s1.y_p = GRID_P * cub3d->input->map->size_y + 1;
	bresenham_line (s1, s2, cub3d, calculate_hex_color(cub3d->input->color_c));
	f1.x_p = t1.x_p;
	f2.x_p = t1.x_p;
	f1.y_p = t2.y_p + 1;
	f2.y_p = WIN_SIZE_Y - 1;
	if (t1.x_p < GRID_P * cub3d->input->map->size_x
		&& f1.y_p <= GRID_P * cub3d->input->map->size_y)
			f1.y_p = GRID_P * cub3d->input->map->size_y + 1;
	bresenham_line (f1, f2, cub3d, calculate_hex_color(cub3d->input->color_f));
	return ;
}
t_tex	*texture_(t_cub *cub3d)
{
	if (cub3d->var->dir == 'N')
		return (cub3d->tex_n);
	if (cub3d->var->dir == 'S')
		return (cub3d->tex_s);
	if (cub3d->var->dir == 'W')
		return (cub3d->tex_w);
	if (cub3d->var->dir == 'E')
		return (cub3d->tex_e);
	return (0);
}
void	put_textured_wall(t_position	t1, t_position	t2, t_cub *cub3d)
{
	t_tex	*tex;

	tex = texture_(cub3d);
	cub3d->var->wall->ty = cub3d->var->wall->ty_off * cub3d->var->wall->ty_step;
	if (cub3d->var->dir == 'S' || cub3d->var->dir == 'N')
		cub3d->var->wall->tx = (int)(cub3d->var->rx * 4) % tex->width;
	else
		cub3d->var->wall->tx = (int)(cub3d->var->ry * 4) % tex->width;
	if (cub3d->var->ra > 90)
		cub3d->var->wall->tx = tex->height - 1 - cub3d->var->wall->tx;
	while (t1.y_p < t2.y_p && (int)cub3d->var->wall->ty  < tex->height)
	{
		if (!(t1.x_p < GRID_P * cub3d->input->map->size_x && t1.y_p < GRID_P * cub3d->input->map->size_y))
		{
			pixel_color(cub3d, t1.x_p, t1.y_p,
				tex->matrix[(int)cub3d->var->wall->ty][(int)cub3d->var->wall->tx]);
		}
		cub3d->var->wall->ty += cub3d->var->wall->ty_step;
		t1.y_p++;
	}
}

void	draw_walls(t_cub *cub3d)
{
	t_position	t1;
	t_position	t2;

	cub3d->var->ca = fix_ang(cub3d->var->pa - cub3d->var->ra);
	cub3d->var->dis_h = cub3d->var->dis_h * cos(deg_to_rad(cub3d->var->ca));
	cub3d->var->line_h = 40000 / (cub3d->var->dis_h);
	cub3d->var->wall->ty_step = texture_(cub3d)->height
		/ (float)cub3d->var->line_h;
	cub3d->var->wall->ty_off = 0;
	if (cub3d->var->line_h > 1200)
	{
		//cub3d->var->wall->ty_off = (cub3d->var->line_h - 1250) * 4;
		cub3d->var->line_h = 1200;
	}
	cub3d->var->line_off = 600 - (cub3d->var->line_h / 2);
	t1.x_p = (cub3d->var->r);
	t1.y_p = cub3d->var->line_off;
	t2.x_p = cub3d->var->r;
	t2.y_p = cub3d->var->line_off + cub3d->var->line_h;
	draw_sky_floor(cub3d, t1, t2);
	put_textured_wall(t1, t2, cub3d);
}
