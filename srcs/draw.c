/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:32:18 by min-kang          #+#    #+#             */

/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	get_height(double dist)
{
	int	h;
	double	c;

	c = 1;
	h = (int) ((SCREEN_Y / dist) * c);
	if (h > SCREEN_Y)
		h = SCREEN_Y;
	return (h);
}

/*
double	anti_fisheye_distortion(double dist, int rayN)
{
	double	incline;

	incline = ANGLE / 2 - rayN * ANGLE / SCREEN_X;
	if (!incline)
		return (dist);
	if (incline < 0)
		incline *= -1;
	double res = dist * cos(incline);
	printf("dist == %f .... height == %f ... angle == %f \n", dist, res, incline);
	return (dist * sin(M_PI / 2 - incline));
}
*/

void	draw_raycast(t_game *game, int h, int rayX)
{
	int	startY;
	int	i;

	startY = (int) ((SCREEN_Y - h) /2);
	i = -1;
	while (++i < h)
		my_mlx_pixel_put(&game->gui, rayX, startY + i, 0x00FFFF00);
}

void	raycast(t_game *game, double angle, int rayN)
{
	t_raycast	ray;

	ray = digital_differential_analyzer(game->map, angle);
	draw_raycast(game, get_height(ray.dist), rayN);
}
                                                                                                                                                
void	draw_cub3D(t_game *game)
{
	double	startAngle;
	double	angle;
	int		rayN;

	startAngle = game->map.theta - ANGLE / 2;
	rayN = -1;
	while (++rayN < SCREEN_X)
	{
		angle = startAngle + (rayN + 1) * ANGLE / SCREEN_X;
		if (angle < 0)
			angle += M_PI * 2;
		if (angle > M_PI * 2)
			angle -= M_PI * 2;
		raycast(game, angle, rayN);
	}
}
