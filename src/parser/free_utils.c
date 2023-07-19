#include "cub3D.h"

int	free_char(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (1);
	while (str[i] != NULL)
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
	return (1);
}

int	free_str(char *str)
{
	free(str);
	str = NULL;
	return (1);
}

void	ft_exit(char *msg, int exit_code)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(exit_code);
}
