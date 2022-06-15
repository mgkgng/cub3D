/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:49:18 by mlecherb          #+#    #+#             */
/*   Updated: 2022/06/15 19:43:22 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_dir(t_game *game)
{
// 	double posX = 22.0, posY = 11.5;  //x and y start position
// 	double dirX = -1.0, dirY = 0.0; //initial direction vector
// 	double planeX = 0.0, planeY = 0.66; //the 2d raycaster version of camera plane
	game->dir.plane_x = 0;
	game->dir.plane_y = 0.66;
	game->dir.dir_x = 0.0;
	game->dir.dir_y = 1.0;
	// game->dir.
}