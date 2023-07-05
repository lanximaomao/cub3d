/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_param.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:39:34 by lsun              #+#    #+#             */
/*   Updated: 2023/07/05 14:12:35 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_param(const char *str, char c)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0' && str[len] != c)
	{
		len++;
	}
	if (str[len] == c)
		return (len + 1);
	return (0);
}
