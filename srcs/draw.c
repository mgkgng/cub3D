/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:32:18 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/18 17:33:01 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	paint_background(t_game *game)
{
	int	i;
	int	j;

	j = -1;
	while (++j < SCREEN_Y / 2)
	{
		i = -1;
		while (++i < SCREEN_X)
			put_pixel(&game->screen, i, j, game->draw.col_ceil);
	}
	j--;
	while (++j < SCREEN_Y)
	{
		i = -1;
		while (++i < SCREEN_X)
			put_pixel(&game->screen, i, j, game->draw.col_floor);
	}	
}

void	draw_raycast(t_game *game, int h, int ray_x)
{
	int	start_y;
	int	i;

	start_y = (int)((SCREEN_Y - h) / 2);
	i = -1;
	while (++i < h)
		put_pixel(&game->screen, ray_x, start_y + i, 0x00FFFF00);
}

void	draw_cub3d(t_game *game)
{
	float	start_angle;
	float	angle;
	int		ray_n;
	t_ray	ray;

	start_angle = game->map.theta - ANGLE / 2;
	ray_n = -1;
	while (++ray_n < SCREEN_X)
	{
		angle = start_angle + (ray_n + 1) * ANGLE / SCREEN_X;
		if (angle < 0)
			angle += M_PI * 2;
		if (angle > M_PI * 2)
			angle -= M_PI * 2;
		ray = digital_differential_analyzer(&game->map, angle);
		draw_img(game, &ray, ray_n, angle);
	}
}

int	redraw(t_game *game)
{
	paint_background(game);
	draw_cub3d(game);
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
	if (game->hook.minimap_on % 2)
		draw_minimap(game);
	return (0);
}

int	draw(t_game *game)
{
	int	i;

	move(game);
	if (game->hook.re)
	{
		redraw(game);
		game->hook.re = false;
	}
	if (game->hook.m_re)
	{
		i = -1;
		while (++i * game->hook.m_sensibility < game->hook.m_turn)
		{
			turn(&game->map, game->hook.m_dir);
			redraw(game);
		}
		game->hook.m_re = false;
	}
	return (0);
}
