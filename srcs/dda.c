/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 11:55:35 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/17 23:50:13 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_ray	get_distX(t_map *map, int *where, float theta)
{
	t_ray	res;
	t_dda	dda;

	ft_bzero(&res, sizeof(t_ray));
	res.dist = INT32_MAX;
	if (!theta || theta == PI)
		return (res);
	if (theta > 0 && theta < PI)
		where[1]++;
	dda = init_dda(theta, 0);
	res.wall.x = map->pos.x + (where[1] - map->pos.y) / tan(theta);
	res.wall.y = where[1];
	while (is_through(map, res.wall.x, res.wall.y + side))
	{
		is_object(&res, map[(int) res.wall.y + side][(int) res.wall.x], map);
		res.wall.x += dda.delta;
		res.wall.y += dda.incre;
	}
	res.dist = perpendicular_dist(map->pos, res.wall, map->theta + PI / 2);
	res.side[1] = dda.side;
	res.side[0] = 0;
	return (res);
}

static t_ray	get_distY(t_map *map, int *where, float theta)
{
	t_ray	res;
	t_dda	dda;
	
	ft_bzero(&res, sizeof(t_ray));
	res.dist = INT32_MAX;
	if (theta == PI / 2 || theta == PI / 2 * 3)
		return (res);
	if ((theta > 0 && theta < PI / 2) || (theta > PI / 2 * 3 && theta < PI * 2))
		where[0]++;
	dda = init_dda(theta, 1);
	res.wall.x = where[0];
	res.wall.y = map->pos.y + (where[0] - map->pos.x) * tan(theta);
	while (is_through(map, res.wall.x + side, res.wall.y))
	{
		is_object(&res, map->map_wall[(int) res.wall.y][(int) res.wall.x + side], map);
		res.wall.x += increX;
		res.wall.y += deltaY;
	}
	res.dist = perpendicular_dist(pos, res.wall, map.theta + PI / 2);
	res.side[0] = side;
	res.side[1] = 0;
	return (res);
}

t_ray	digital_differential_analyzer(t_map *map, float theta, t_game *game)
{
	t_ray	res_x;
	t_ray	res_y;

	res_x = get_distX(map, map->pos, (int [2]) {(int) map.pos.x, (int) map.pos.y}, theta);
	res_y = get_distY(map, map->pos, (int [2]) {(int) map.pos.x, (int) map.pos.y}, theta);
	if (res_x.dist < res_y.dist)
	{
		game->side = 0;
		combine_list(res_x.dist, &res_x.door, res_y.door);
		combine_list(res_x.dist, &res_x.sprite, res_y.sprite);
		free_lst(res_y.door);
		return (res_x);
	}
	game->side = 1;
	combine_list(res_y.dist, &res_y.door, res_x.door);
	combine_list(res_y.dist, &res_y.sprite, res_x.door);
	free_lst(res_x.door);
	return (res_y);
}
