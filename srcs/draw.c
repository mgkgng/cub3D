/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:32:18 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/16 14:52:36 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	get_height(double dist)
{
	int	h;
	double	c;

	c = 0.7;
	h = (int) ((SCREEN_Y / dist) * c);
	if (h > SCREEN_Y)
		h = SCREEN_Y;
	return (h);
}

double	anti_fisheye_distortion(double dist, int rayN)
{
	double	incline;

	incline = fabs(rayN * DEG - ANGLE / 2);
	if (!incline)
		return (dist);
	return (dist * sin(M_PI / 2 - incline));
}

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
	t_raycast	rayDist;

	rayDist = digital_differential_analyzer(game->map, angle);
	// there was an error with anti_fisheye_distortion function
	draw_raycast(game, get_height(rayDist.dist), rayN);
}

void	draw_cub3D(t_game *game)
{
	double	startAngle;
	int		rayN;

	startAngle = game->map.theta + ANGLE / 2;
	rayN = -1;
	while (++rayN < SCREEN_X)
		raycast(game, startAngle - (rayN + 1) * ANGLE / SCREEN_X, rayN);
}