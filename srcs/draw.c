/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:32:18 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/14 18:32:58 by min-kang         ###   ########.fr       */
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

void	draw_raycast(t_game game, int h, int rayN)
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
			my_mlx_pixel_put(&game.gui, startX + i, startY + j, 0xFFFF00);
	}
}

void	raycast(t_game game, double angle, int rayN)
{
	t_raycast	rayDist;
	double		r;

	rayDist = digital_differential_analyzer(game.map.pos, game.map.map2d, angle);
	draw_raycast(game, get_hight(anti_fisheye_distortion(rayDist.dist)), rayN);
}

void	draw_cub3D(t_game game)
{
	int		ray;
	double	startAngle;
	int		i;

	r = M_PI / 180;
	startAngle = game.map.theta - r * ANGLE / 2;
	i = -1;
	while (++i < ANGLE)
		raycast(game, startAngle + r * i, i);
}