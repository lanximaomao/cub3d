#include "cub3D.h"

void	flood_fill(t_cub *cub, int row, int col, char old)
{
	if (row >= cub->input->map->size_y || col >= cub->input->map->size_x
		|| col < 0 || row < 0 || cub->input->map->matrix[row][col] != old)
		return ;
	else
	{
		cub->input->map->matrix[row][col] = old + 1;
		flood_fill(cub, row, col + 1, old);
		flood_fill(cub, row, col - 1, old);
		flood_fill(cub, row + 1, col, old);
		flood_fill(cub, row - 1, col, old);
	}
}
