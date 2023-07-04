#include "cub3D.h"

static void	free_double_pointer(void **pointer, int size)
{
	int		i;

	i = 0;
	if (!pointer)
		return ;
	while (i <= size)
	{
		free(pointer[i]);
		i++;
	}
	free(pointer);
}
