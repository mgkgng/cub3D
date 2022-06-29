/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <min-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 15:38:35 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/29 15:46:19 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_max_index(float *dist, int nb, int already)
{
	int	i;
	int	max;
	int	res;

	i = -1;
	max = INT32_MIN;
	res = 0;
	while (++i < nb)
	{
		if (dist[i] > max && (already == -1 || dist[i] < dist[already]))
		{
			max = dist[i];
			res = i;
		}
	}
	return (res);
}

int	*sort_sprites(t_map *map, int nb)
{
	int	i;
	int	*res;
	int	already;
	int	max;

	float	*spr_dist = ft_calloc(nb, sizeof(float));
    for(int i = 0; i < nb; i++)
    {
		spr_dist[i] = pow(map->pos.x - map->spr[i].x, 2)
			+ pow(map->pos.y - map->spr[i].y, 2);
	}
	res = ft_calloc(nb, sizeof(int));
	i = -1;
	already = -1;
	while (++i < nb)
	{
		max = find_max_index(spr_dist, nb, already);
		res[i] = max;
		already = max;
	}
	free(spr_dist);
	return (res);
}

t_sprite	get_sprite_info(t_game *game, float *dist, t_point spr)
{
	t_sprite	res;

	res.x = spr.x - game->map.pos.x;
	res.y = spr.y - game->map.pos.y;
	res.inverse = 1.0f / (game->camera.plane_x * game->camera.dir_y - game->camera.dir_x * game->camera.plane_y);
	res.x_trans = res.inverse * (game->camera.dir_y * res.x - game->camera.dir_x * res.y);
	res.y_trans = res.inverse * (game->camera.plane_x * res.y - game->camera.plane_y * res.x);
	res.x_screen = SCREEN_X / 2 * (1 + res.x_trans / res.y_trans);
	res.h = SCREEN_Y / res.y_trans;
	res.start_y = (SCREEN_Y - res.h) / 2;
	if (res.start_y < 0)
		res.start_y = 0;
	res.end_y = (SCREEN_Y + res.h) / 2;
	if (res.end_y >= SCREEN_Y)
	    res.end_y = SCREEN_Y - 1;
	res.w = SCREEN_Y / res.y_trans;
	res.start_x = res.x_screen - res.w / 2;
	if (res.start_x < 0)
		res.start_x = 0;
	res.end_x = res.w / 2 + res.x_screen;
	if (res.end_x >= SCREEN_X)
		res.end_x = SCREEN_X;
	return (res);
}

void    put_sprite(t_game *game, t_sprite spr_info, t_img img, int x)
{
    int y;
    int tex_x;
    int tex_y;
    int d;

	while (++x < spr_info.end_x)
	{
		int tex_x = (int)(256 * (x - (spr_info.x_screen - spr_info.w / 2)) * 64 / spr_info.w) / 256;
		int y = spr_info.start_y - 1;
		while (++y < spr_info.end_y)
		{
			int d = y * 256 - SCREEN_Y * 128 + spr_info.h * 128;
			int tex_y = ((d * 64) / spr_info.h) / 256;
			put_pixel(&game->screen, x, y, get_data_color(tex_x, tex_y, img.addr, img));
		}
	}
}

void	draw_sprite(t_game *game, float *dist, t_img img)
{
	int			i;
	int			x;
	int		    y;
	t_sprite	spr_info;
	int			*spr_sort;

	if (!game->map.spr_nb)
		return ;
	spr_sort = sort_sprites(&game->map, game->map.spr_nb);
	i = -1;
	while(++i < game->map.spr_nb)
	{
		spr_info = get_sprite_info(game, dist, game->map.spr[spr_sort[i]]);
		x = spr_info.start_x - 1;
        if (spr_info.y_trans <= 0 || x <= 0 || x >= SCREEN_X || spr_info.y_trans >= dist[i])
            continue;
        put_sprite(game, spr_info, img, x);
	}
    free(spr_sort);
}