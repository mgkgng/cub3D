/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:32:18 by min-kang          #+#    #+#             */
/*   Updated: 2022/05/12 19:23:59 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	get_height(double dist, t_game *game)
{
	int		h;

	h = (int)(SCREEN_Y / dist);
	if (h > SCREEN_Y)
	{
		game->height = h;
		h = SCREEN_Y;
	}
	else
		game->height = h;
	return (h);
}

void	draw_raycast(t_game *game, int h, int ray_x)
{
	int	start_y;
	int	i;

	start_y = (int)((SCREEN_Y - h) / 2);
	i = -1;
	printf("Start Y : %i\n", start_y);
	while (++i < h)
		my_mlx_pixel_put(&game->gui, ray_x, start_y + i, 0x00FFFF00);
}

void	raycast(t_game *game, double angle, int rayN, t_text *t)
{
	t_raycast	ray;
	ray = digital_differential_analyzer(game->map, angle);
	draw_raycast(game, get_height(ray.dist, game), rayN);
	// draw_text(game, get_height(ray.dist, game), ray, rayN, t);
}

void	draw_cub3D(t_game *game)
{
	double	start_angle;
	double	angle;
	int		ray;
	t_text	*t;

	t = t_init();
	t->img = mlx_xpm_file_to_image(game->gui.mlx, "./texture/wall.xpm", &t->w, &t->h);
	t->addr = mlx_get_data_addr(t->img, &t->bits_per_pixel, &t->line_length, &t->endian);

	start_angle = game->map.theta - ANGLE / 2;
	ray = -1;
	while (++ray < SCREEN_X)
	{
		angle = start_angle + (ray + 1) * ANGLE / SCREEN_X;
		if (angle < 0)
			angle += M_PI * 2;
		if (angle > M_PI * 2)
			angle -= M_PI * 2;
		raycast(game, angle, ray, t);
	}
}
