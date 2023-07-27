/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linlinsun <linlinsun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:40:45 by asarikha          #+#    #+#             */
/*   Updated: 2023/07/28 00:25:37 by linlinsun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	message(char *str1, int errno)
{
	ft_putstr_fd("cub: ", 2);
	ft_putstr_fd(str1, 2);
	return (errno);
}
