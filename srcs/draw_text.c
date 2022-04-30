/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 17:46:05 by mlecherb          #+#    #+#             */
/*   Updated: 2022/04/30 18:52:36 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// int	wich_texture(t_game *game, t_raycast ray)
// {

// }

void	draw_text(t_game *game, int h, int x, t_raycast ray)
{
	// int	fd;

	// fd = open(game->draw.nswe[wich_texture(game, ray)], O_RDONLY);
	// Essaye avec une texture partout
	int	startY;
	int	i;
	int	line; // C'est la ligne de l'image qu'on doit afficher;

	line = (int) ray.wall.x;
	line = line * // Longueur longeur de l'image;
	startY = (int) ((SCREEN_Y - h) /2);
	i = 0;
	
}