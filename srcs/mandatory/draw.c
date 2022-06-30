/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:37:41 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/30 22:57:40 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_m.h"

static void	draw_wall(t_game *game, t_ray ray, int ray_n, float angle)
{
	int				start;
	int				h;
	unsigned int	color;
	t_tex_info		info;
	int				i;

	h = get_height(ray.dist, game);
	if (game->height > 600)
		h = h / ray.dist;
	start = 0;
	if (h < SCREEN_Y)
		start = (SCREEN_Y - h) / 2;
	info = get_tex_info(ray.wall, h, start);
	info.img = which_texture(ray.wall_side, &game->texture, angle);
	i = -1;
	while (++i < h && i < SCREEN_Y)
	{
		info.y = (int) info.tex_pos & (64 - 1);
		info.tex_pos += info.step;
		color = get_data_color(info.x, info.y, info.img.addr, info.img);
		put_pixel(&game->screen, ray_n, start + i, color);
	}
}

static void	draw_by_ray(t_game *game)
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
		draw_wall(game, ray, ray_n, angle);
	}
}

int	draw(t_game *game)
{
	move(game);
	if (game->hook.re)
	{
		paint_background(game);
		draw_by_ray(game);
		mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
		game->hook.re = false;
	}
	return (0);
}