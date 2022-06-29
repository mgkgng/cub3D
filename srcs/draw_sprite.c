/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 15:38:35 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/29 21:48:50 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	find_max_index(float *dist, int nb, int already)
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

/*static int	*sort_sprites(t_map *map, int nb)
{
	int		i;
	int		*res;
	int		already;
	int		max;
	float	*spr_dist;

	spr_dist = ft_calloc(nb, sizeof(float));
	i = -1;
	while (++i < nb)
		spr_dist[i] = pow(map->pos.x - map->spr[i].x, 2)
			+ pow(map->pos.y - map->spr[i].y, 2);
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
}*/
int	*sort_sprites(float *dist, int nb)
{
	int	i;
	int	*res;
	int	already;
	int	max;

	res = ft_calloc(nb, sizeof(int));
	i = -1;
	already = -1;
	while (++i < nb)
	{
		max = find_max_index(dist, nb, already);
		res[i] = max;
		already = max;
	}
	return (res);
}

/*static t_sprite	get_sprite_info(t_camera camera, t_point spr, t_point pos)
{
	t_sprite	res;

	res.x = spr.x - pos.x;
	res.y = spr.y - pos.y;
	res.c = 1.0f / (camera.plane_x * camera.dir_y
			- camera.dir_x * camera.plane_y);
	res.x_trans = res.c * (camera.dir_y * res.x - camera.dir_x * res.y);
	res.y_trans = res.c * (camera.plane_x * res.y - camera.plane_y * res.x);
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

static void	put_sprite(t_game *game, t_sprite spr_info, float *dist, t_img img)
{
	int	x;
	int	y;
	int	tex_x;
	int	tex_y;
	int	d;

	x = spr_info.start_x - 1;
	while (++x < spr_info.end_x)
	{
		tex_x = (int)(256 * (x - (spr_info.x_screen - spr_info.w / 2))
				* 64 / spr_info.w) / 256;
		if (spr_info.y_trans > 0 && x > 0
			&& x < SCREEN_X && spr_info.y_trans < dist[x])
		{
			y = spr_info.start_y - 1;
			while (++y < spr_info.end_y)
			{
				printf("why?\n");
				d = y * 256 - SCREEN_Y * 128 + spr_info.h * 128;
				tex_y = ((d * 64) / spr_info.h) / 256;
				put_pixel(&game->screen, x, y,
					get_data_color(tex_x, tex_y, img.addr, img));
			}
		}
	}
}

void	draw_sprite(t_game *game, t_map *map, float *dist, t_img img)
{
	int			i;
	t_sprite	spr_info;
	int			*spr_sort;

	spr_sort = sort_sprites(map, map->spr_nb);
	i = -1;
	while (++i < map->spr_nb)
	{
		spr_info = get_sprite_info(map->camera,
				map->spr[spr_sort[i]], map->pos);
		printf("y_trans: %f... start_x: %d...\n", spr_info.y_trans, spr_info.start_x);
		put_sprite(game, spr_info, dist, img);
	}
	free(spr_sort);
}*/

void	draw_sprite(t_game *game, t_map *map, float *dist, t_img img)
{
	int	sprite_nb;
	int	i;

	if (!game->map.spr)
		return ;
	sprite_nb = 0;
	i = -1;
	while (game->map.spr[++i].x != -1)
		sprite_nb++;

	float	*spr_dist = ft_calloc(sprite_nb, sizeof(float));
    for(int i = 0; i < sprite_nb; i++)
    {
		spr_dist[i] = pow(game->map.pos.x - game->map.spr[i].x, 2)
			+ pow(game->map.pos.y - game->map.spr[i].y, 2);
	}
	int *spr_sort = sort_sprites(spr_dist, sprite_nb);

    for(int i = 0; i < sprite_nb; i++)
	{
		float spr_x = game->map.spr[spr_sort[i]].x - game->map.pos.x;
		float spr_y = game->map.spr[spr_sort[i]].y - game->map.pos.y;
		float	inverse = 1.0f / (map->camera.plane_x * map->camera.dir_y - map->camera.dir_x * map->camera.plane_y); //required for correct matrix multiplication
		float transform_x = inverse * (map->camera.dir_y * spr_x - map->camera.dir_x * spr_y);
		float transform_y = inverse * (map->camera.plane_x * spr_y - map->camera.plane_y * spr_x); //this is actually the depth inside the screen, that what Z is in 3D
		int spr_screen_x = SCREEN_X / 2 * (1 + transform_x / transform_y);
		float spr_h = SCREEN_Y / transform_y;
		int start_y = (SCREEN_Y - spr_h) / 2;
		if(start_y < 0)
			start_y = 0;
		int end_y = (SCREEN_Y + spr_h) / 2;
		if(end_y >= SCREEN_Y)
		end_y = SCREEN_Y - 1;

		float spr_width = SCREEN_Y / transform_y;
		int start_x = spr_screen_x - spr_width / 2;
		if (start_x < 0)
			start_x = 0;
		int end_x = spr_width / 2 + spr_screen_x;
		if (end_x >= SCREEN_X)
			end_x = SCREEN_X;
		printf("%d.. start_x\n", start_x);
		int	i = start_x - 1;
		while (++i < end_x)
		{
			int tex_x = (int)(256 * (i - (spr_screen_x - spr_width / 2)) * 64 / spr_width) / 256;
			if (transform_y > 0 && i > 0 && i < SCREEN_X && transform_y < dist[i])
			{
				int j = start_y - 1;
				while (++j < end_y)
				{
					int d = j * 256 - SCREEN_Y * 128 + spr_h * 128;
					int tex_y = ((d * 64) / spr_h) / 256;
					unsigned int color = get_data_color(tex_x, tex_y, img.addr, img);
					put_pixel(&game->screen, i, j, color);
				}
			}
		}
	}
}