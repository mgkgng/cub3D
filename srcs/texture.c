/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:49:18 by mlecherb          #+#    #+#             */
/*   Updated: 2022/06/16 14:59:46 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_dir(t_game *game)
{
	game->dir.plane_x = 0;
	game->dir.plane_y = 0.66;
	game->dir.dir_x = -1.0;
	game->dir.dir_y = 0.0;
}