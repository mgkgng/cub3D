/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:32:18 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/07 20:17:48 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// 1. need to implement dda
// 2. need to implement raycast
// 3. need to implement the function giving the height regard of the distance between the character's point and the wall

// dda is going to return the distance

// ** should only consider the fact that north and the south (y-axis) is inverted.
// ** should also consider that fact the slope of the peripendular line of y-axis will be given as inf through atan.

int	digital_differential_analyzer(t_point pos, t_point dir, char **map, int theta)
{
	int	step;
	int	start;

	if ((theta > 45 && theta < 135) || (theta > 225 && theta < 315))
		start = pos.y;
	else
		start = pos.x;
	step = 
}

void	raycast(t_point pos, char **map, int theta)
{
	// ça c'est une idee geniale ;)
	t_point	dir;
	double	dist;

	dir.x = pos.x + cos(theta);
	dir.y = pos.y + sin(theta);
	dist = digital_differential_analyzer(pos, dir, map, theta);
	// need height/distance calculator here
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