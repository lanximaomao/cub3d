/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:31:11 by asarikha          #+#    #+#             */
/*   Updated: 2023/07/03 15:42:40 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# define GRID_P 64
# define PLAYER_P 4
# define PLAYE_S 5
# define BLACK 0x000000
# define WHITE 0xffffff
# define GREEN 0x009933
# define RED 0xff0000
# define TURQUOISE 0x00cccc
# define YELLOW 0xffff00
# define PURPLE 0x800080
# define PINK 0xff33cc

void	draw_map2d(t_cub *cub3d);
void	draw_player2d(t_cub *cub3d);
void	draw_rays2d(t_cub *cub3d);

#endif