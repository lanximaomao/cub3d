/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_filetype.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:41:54 by asarikha          #+#    #+#             */
/*   Updated: 2023/07/27 13:05:26 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
