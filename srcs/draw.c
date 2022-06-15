/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:58:47 by mlecherb          #+#    #+#             */
/*   Updated: 2022/06/15 16:50:44 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_raycast(t_game *game, int h, int ray_x)
{
	int	start_y;
	int	i;

	start_y = (int)((SCREEN_Y - h) / 2);
	i = -1;
	while (++i < h)
		my_mlx_pixel_put(&game->gui, ray_x, start_y + i, 0x00FFFF00);
}

void	raycast(t_game *game, float angle, int rayN)
{
	t_raycast	ray;
	
	ray = digital_differential_analyzer(game->map, angle, game);
	draw_img(game, ray, rayN);
}

void	draw_cub3D(t_game *game)
{
	float	start_angle;
	float	angle;
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
