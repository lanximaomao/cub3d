#include "cub3D.h"

/*
** only filename end with .cub, not .cub3 or.crab
*/
int	valid_filetype(char *str)
{
	char	*ret;

	ret = ft_strnstr(str, ".cub", ft_strlen(str));
	if (!ret)
		return (-1);
	if (*(ret + 4) != '\0')
		return (-1);
	return (1);
}
