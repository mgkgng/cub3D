/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:32:18 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/14 11:59:26 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

void	draw_raycast(t_map map, int h)
{
	double	startY;

	startY = (SCREEN_Y - h) /2;
}

void	raycast(t_map map, double angle)
{
	t_raycast	res;

	res = digital_differential_analyzer(map.pos, map.map2d, angle);
	draw_raycast(map, get_hight(anti_fisheye_distortion(res.dist)));
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