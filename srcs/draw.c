/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:32:18 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/07 19:55:46 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// 1. need to implement dda
// 2. need to implement raycast
// 3. need to implement the function giving the height regard of the distance between the character's point and the wall

// dda is going to return the distance
int	digital_differential_analyzer(t_point pos, t_point dir, char **map, int theta)
{
	int	increment;
	int	start;

	if ((theta > 45 && theta < 135) || (theta > 225 && theta < 315))
		start = pos.y;
	else
		start = pos.x;
}

void	raycast(t_point pos, char **map, int theta)
{
	// ça c'est une idee geniale ;)
	t_point	dir;

	dir.x = pos.x + cos(theta);
	dir.y = pos.y + sin(theta);
}

int draw(t_map map, t_raycast rc)
{
	int	i;

	i = -1;
	while (++i < ANGLE / 2)
	{
		// left
		raycast(map.pos, map.map2d, map.theta - i);
		// right 
		raycast(map.pos, map.map2d, map.theta + i);
	}
}