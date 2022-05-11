/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:32:18 by min-kang          #+#    #+#             */
/*   Updated: 2022/05/10 20:26:43 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	get_height(double dist)
{
	int		h;

	h = (int)(SCREEN_Y / dist);
	if (h > SCREEN_Y)
		h = SCREEN_Y;
	return (h);
}

void	draw_raycast(t_game *game, int h, int ray_x)
{
	int	start_y;
	int	i;

	start_y = (int)((SCREEN_Y - h) / 2);
	i = -1;
	while (++i < h)
		my_mlx_pixel_put(&game->gui, ray_x, start_y + i, 0x00FFFF00);
}

void	raycast(t_game *game, double angle, int rayN)
{
	t_raycast	ray;

	ray = digital_differential_analyzer(game->map, angle);
	draw_raycast(game, get_height(ray.dist), rayN);
}

void	draw_cub3d(t_game *game)
{
	double	start_angle;
	double	angle;
	int		ray;

	start_angle = game->map.theta - ANGLE / 2;
	ray = -1;
	while (++ray < SCREEN_X)
	{
		angle = start_angle + (ray + 1) * ANGLE / SCREEN_X;
		if (angle < 0)
			angle += M_PI * 2;
		if (angle > M_PI * 2)
			angle -= M_PI * 2;
		raycast(game, angle, ray);
	}
}
