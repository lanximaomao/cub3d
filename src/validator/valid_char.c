#include "cub3D.h"

/*
** only '1', ' ', '0', 'N', 'S', 'W', 'E' and '\n are valid chars
*/
int	valid_char(char *str)
{
	int	player_flag;
	int	wall_flag;

	player_flag = 0;
	wall_flag = 0;
	while (*str)
	{
		if (*str == '1')
			wall_flag = 1;
		if (*str != '\n' && *str != '0' && *str != '1' && *str != ' ')
		{
			if (*str == 'N' || *str == 'S' || *str == 'W' || *str == 'E')
				player_flag++;
			else
				ft_exit("Error: invalid chars", 3);
		}
		str++;
	}
	if (player_flag != 1)
		ft_exit("Error: player error", 3);
	if (wall_flag == 0)
		ft_exit("Error: no wall?", 3);
	return (0);
}
