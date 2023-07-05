#include "../includes/cub3D.h"
#include "../includes/libft.h"
#include "../includes/get_next_line.h"

// free_char
void	free_char(char **input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i])
	{
		free(input[i]);
		i++;
	}
	free(input);
}

void ft_exit(char* msg, int exit_code)
{
	perror(msg);
	exit(exit_code);
}
