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

void	draw_walls(t_cub *cub3d)
{
	t_position	t1;
	t_position	t2;
	int			i;

	cub3d->var->ca = fix_ang(cub3d->var->pa - cub3d->var->ra);
	cub3d->var->dis_h = cub3d->var->dis_h * cos(deg_to_rad(cub3d->var->ca));
	cub3d->var->line_h = 40000 / (cub3d->var->dis_h);
	if (cub3d->var->line_h > 1200)
		cub3d->var->line_h = 1200;
	cub3d->var->line_off = 600 - (cub3d->var->line_h / 2);
	t1.x_p = (cub3d->var->r) * 2;
	t1.y_p = cub3d->var->line_off;
	t2.x_p = cub3d->var->r * 2;
	t2.y_p = cub3d->var->line_off + cub3d->var->line_h;
	i = -1;
	while (++i < 2)
	{
		draw_sky_floor(cub3d, t1, t2);
		if (t1.x_p < GRID_P * cub3d->input->map->size_x
			&& t1.y_p < GRID_P * cub3d->input->map->size_y)
			t1.y_p = GRID_P * cub3d->input->map->size_y;
		bresenham_line (t1, t2, cub3d, YELLOW);
		//put_texture_to_wall(cub3d)
		t1.x_p++;
		t2.x_p++;
	}
}
