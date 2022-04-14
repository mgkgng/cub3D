/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:32:18 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/14 11:55:33 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// 3. need to implement the function giving the height regard of the distance between the character's point and the wall

// ** should only consider the fact that north and the south (y-axis) is inverted.




double	get_height(double dist)
{
	int	h;
	double	c;

	c = 0.5;
	h = (int) ((SCREEN_Y / dist) * c);
	if (h > SCREEN_Y)
		h = SCREEN_Y;
	return (h);
}

double	anti_fisheye_distortion(double dist)
{
	
}

void	draw_raycast(int h, int mapSize)
{
	double	startY;

	startY = (SCREEN_Y - h) /2;
}

void	raycast(t_map map, double angle)
{
	t_raycast	res;
	res = digital_differential_analyzer(map.pos, map.map2d, angle);
	// anti-fisheye-distortion
	draw_raycast(get_hight(res.dist), map.width * map.height)
	// need height/distance calculator here
}

int draw(t_map map)
{
	double	r;

	raycast(map.pos, map.map2d, map.theta);
	r = M_PI / 180;
	while (r < ANGLE / 2)
	{
		raycast(map, map.theta - r);
		raycast(map, map.theta + r);
		r += M_PI / 180;
	}
	return (0);
}