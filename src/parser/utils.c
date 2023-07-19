#include "cub3D.h"

int	array_size(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

int	how_many(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	ft_atoi_isnum(const char *str)
{
	long	result;
	int		sign;

	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	if (*str != '\0' && (*str < 9 || *str > 13))
		return (-1);
	if (result * sign >= 0 && result * sign <= 255)
		return (result * sign);
	return (-1);
}

int	loop(t_cub *cub, FunctionPointer member)
{
	int	row;
	int	col;

	row = 0;
	while (row < cub->input->map->size_y)
	{
		col = 0;
		while (col < cub->input->map->size_x)
		{
			member(cub);
			col++;
		}
		row++;
	}
	return (SUCCESS);
}
