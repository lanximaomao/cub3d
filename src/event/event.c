#include "cub3D.h"

float	fix_ang(float a)
{
	if (a > 359)
	{
		a -= 360;
	}
	if (a < 0)
	{
		a += 360;
	}
	return (a);
}

int	key_press(int keycode, t_cub *cub)
{
	if (keycode == KEY_W)
		cub->key->w = 1;
	if (keycode == KEY_A)
		cub->key->a = 1;
	if (keycode == KEY_D)
		cub->key->d = 1;
	if (keycode == KEY_S)
		cub->key->s = 1;
	if (keycode == KEY_LEFT)
		cub->key->left = 1;
	if (keycode == KEY_RIGHT)
		cub->key->right = 1;
	if (keycode == KEY_UP)
		cub->key->up = 1;
	if (keycode == KEY_DOWN)
		cub->key->down = 1;
	key_event(keycode, cub);
	return (0);
}

int	key_release(int keycode, t_cub *cub)
{
	if (keycode == KEY_W)
		cub->key->w = 0;
	if (keycode == KEY_A)
		cub->key->a = 0;
	if (keycode == KEY_D)
		cub->key->d = 0;
	if (keycode == KEY_S)
		cub->key->s = 0;
	if (keycode == KEY_LEFT)
		cub->key->left = 0;
	if (keycode == KEY_RIGHT)
		cub->key->right = 0;
	if (keycode == KEY_UP)
		cub->key->up = 0;
	if (keycode == KEY_DOWN)
		cub->key->down = 0;
	return (0);
}
