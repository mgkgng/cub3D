/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 16:49:55 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/30 22:53:09 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_b.h"

float	get_height(float dist, t_game *game)
{
	int		h;

	h = SCREEN_Y / dist;
	if (h > SCREEN_Y)
	{
		game->height = h;
		h = SCREEN_Y;
	}
	else
		game->height = h;
	return (h);
}

unsigned int	get_data_color(int x, int y, void *addr, t_img img)
{
	char	*dst;

	dst = addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

t_tex_info	get_tex_info(t_point wall, int h, int start)
{
	t_tex_info	info;

	if (wall.x - (int) wall.x == 0)
		info.fract = wall.y - (int) wall.y;
	else
		info.fract = wall.x - (int) wall.x;
	info.step = 64.0f / (float) h;
	info.x = info.fract * 64;
	info.tex_pos = (start - (600 - h + 1) / 2) * info.step;
	return (info);
}

t_img	which_texture(t_ray ray, t_map *map, t_texture *text, float angle)
{
	int	pos[2];

	pos[1] = (int) ray.wall.y + ray.side[1];
	pos[0] = (int) ray.wall.x + ray.side[0];
	if (map->map_wall[pos[1]][pos[0]] == 'D')
		return (text->door_c);
	else if (ray.wall_side == 1)
	{
		if (angle <= 3 * PI / 2 && angle >= PI / 2)
			return (text->wall_w);
		return (text->wall_e);
	}
	else
	{
		if (angle > PI && angle < 2 * PI)
			return (text->wall_n);
		return (text->wall_s);
	}
}

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
