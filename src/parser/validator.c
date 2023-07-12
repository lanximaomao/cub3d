//what is a valid map?

/*
** 1. only contains 6 possible characters, 0, 1, N, S, E, W
** 2. closed/surrounded by walls
** 3. if one more , at the end of the color code?
*/

#include <stdio.h>

int valid_char(char* str)
{
	int i;
	int player_flag;

	i = 0;
	player_flag = 0;
	while (str[i])
	{
		printf("%c", str[i]);
		if (str[i] != '\n' && str[i] != '0' && str[i] != '1' &&  str[i] != ' ')
		{
			if (str[i] == 'N' || str[i] == 'S' || str[i] == 'W'|| str[i] == 'E' )
				player_flag++;
			else
				return (-1);
		}
		i++;
	}
	if (player_flag != 1)
		return (-1);
	return (0);
}

