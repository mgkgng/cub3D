/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:32:18 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/14 18:24:51 by min-kang         ###   ########.fr       */
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

void	draw_raycast(t_map map, int h, int rayN)
{
	double	startX;
	double	startY;
	int		pixNbX;
	int		i;
	int		j;

	pixNbX = startX / ANGLE;
	startX = rayN * pixNbX;
	startY = (SCREEN_Y - h) /2;
	i = -1;
	while (++i < pixNbX)
	{
		j = -1;
		while (++j < h)
			my_mlx_pixel_put(gui, startX + i, startY + j, 0xFFFF00);
	}
}

void	raycast(t_map map, double angle, int rayN)
{
	t_raycast	res;
	double		r;

	res = digital_differential_analyzer(map.pos, map.map2d, angle);
	draw_raycast(map, get_hight(anti_fisheye_distortion(res.dist)), rayN);
}

int draw(t_map map)
{
	int		ray;
	double	startAngle;
	int		i;

	r = M_PI / 180;
	startAngle = map.theta - r * ANGLE / 2;
	i = -1;
	while (++i < ANGLE)
		raycast(map, startAngle + r * i, i);
	return (0);
}