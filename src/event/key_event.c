#include "cub3D.h"

static void	calculate_next(t_cub *cub)
{
	cub->key->xo = 0;
	if (cub->var->pdx < 0)
		cub->key->xo = -PLAYER_OFF;
	else
		cub->key->xo = PLAYER_OFF;
	cub->key->yo = 0;
	if (cub->var->pdy < 0)
		cub->key->yo = -PLAYER_OFF;
	else
		cub->key->yo = PLAYER_OFF;
	cub->key->ipx = cub->var->px / GRID_P;
	cub->key->ipx_add_xo = (cub->var->px + cub->key->xo) / GRID_P;
	cub->key->ipx_sub_xo = (cub->var->px - cub->key->xo) / GRID_P;
	cub->key->ipy = cub->var->py / GRID_P;
	cub->key->ipy_add_yo = (cub->var->py + cub->key->yo) / GRID_P;
	cub->key->ipy_sub_yo = (cub->var->py - cub->key->yo) / GRID_P;
}

static void	move_up_down(int dir, t_cub *cub)
{
	calculate_next(cub);
	if (dir == KEY_DOWN)
	{
		if (cub->input->map->matrix[cub->key->ipy]
			[cub->key->ipx_sub_xo] != '1')
			cub->var->px -= cub->var->pdx * PLAYER_S;
		if (cub->input->map->matrix[cub->key->ipy_sub_yo]
			[cub->key->ipx] != '1')
			cub->var->py -= cub->var->pdy * PLAYER_S;
	}
	if (dir == KEY_UP)
	{
		if (cub->input->map->matrix[cub->key->ipy]
			[cub->key->ipx_add_xo] != '1')
			cub->var->px += cub->var->pdx * PLAYER_S;
		if (cub->input->map->matrix[cub->key->ipy_add_yo]
			[cub->key->ipx] != '1')
			cub->var->py += cub->var->pdy * PLAYER_S;
	}
}

static void	move_right_left(int dir, t_cub *cub)
{
	if (dir == KEY_LEFT)
	{
		cub->var->pa += 90;
		cub->var->pdx = cos(deg_to_rad(cub->var->pa));
		cub->var->pdy = -sin(deg_to_rad(cub->var->pa));
		move_up_down(KEY_UP, cub);
		cub->var->pa -= 90;
	}
	if (dir == KEY_RIGHT)
	{
		cub->var->pa -= 90;
		cub->var->pdx = cos(deg_to_rad(cub->var->pa));
		cub->var->pdy = -sin(deg_to_rad(cub->var->pa));
		move_up_down(KEY_UP, cub);
		cub->var->pa += 90;
	}
}

static void	move_ang(int ang, t_cub *cub)
{
	if (ang == KEY_LEFT)
	{
		cub->var->pa = fix_ang(cub->var->pa + PLAYER_S);
		cub->var->pdx = cos(deg_to_rad(cub->var->pa));
		cub->var->pdy = -sin(deg_to_rad(cub->var->pa));
	}
	if (ang == KEY_RIGHT)
	{
		cub->var->pa = fix_ang(cub->var->pa - PLAYER_S);
		cub->var->pdx = cos(deg_to_rad(cub->var->pa));
		cub->var->pdy = -sin(deg_to_rad(cub->var->pa));
	}
}

int	key_event(int keycode, t_cub *cub)
{
	cub->var->pdx = cos(deg_to_rad(cub->var->pa));
	cub->var->pdy = -sin(deg_to_rad(cub->var->pa));
	if (keycode == KEY_ESC)
		end_cub(cub);
	else if (keycode == KEY_UP || keycode == KEY_W)
		move_up_down(KEY_UP, cub);
	else if (keycode == KEY_DOWN || keycode == KEY_S)
		move_up_down(KEY_DOWN, cub);
	else if (keycode == KEY_LEFT)
		move_ang(KEY_LEFT, cub);
	else if (keycode == KEY_A)
		move_right_left(KEY_LEFT, cub);
	else if (keycode == KEY_RIGHT)
		move_ang(KEY_RIGHT, cub);
	else if (keycode == KEY_D)
		move_right_left(KEY_RIGHT, cub);
	cub->input->position->y_p = cub->var->px - 2;
	cub->input->position->x_p = cub->var->py - 2;
	render(cub);
	return (0);
}
