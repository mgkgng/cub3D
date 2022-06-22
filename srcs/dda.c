/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 11:55:35 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/22 21:02:46 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_ray	get_dist_x(t_map *map, int *where, float theta)
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
	res.side[0] = 0;
	res.side[1] = dda.side;
	res.wall.x = map->pos.x + (where[1] - map->pos.y) / tan(theta);
	res.wall.y = where[1];
	while (is_through(map, res.wall.x, res.wall.y + dda.side))
	{
		is_object(&res, map,
			(int [2]){(int) res.wall.y + dda.side, (int) res.wall.x}, 0);
		res.wall.x += dda.delta;
		res.wall.y += dda.incre;
	}
	res.dist = perpendicular_dist(map->pos, res.wall, map->theta + PI / 2);

	return (res);
}

static t_ray	get_dist_y(t_map *map, int *where, float theta)
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
	res.side[0] = dda.side;
	res.side[1] = 0;
	res.wall.x = where[0];
	res.wall.y = map->pos.y + (where[0] - map->pos.x) * tan(theta);
	while (is_through(map, res.wall.x + dda.side, res.wall.y))
	{
		is_object(&res, map,
			(int [2]){(int) res.wall.y, (int) res.wall.x + dda.side}, 1);
		res.wall.x += dda.incre;
		res.wall.y += dda.delta;
	}
	res.dist = perpendicular_dist(map->pos, res.wall, map->theta + PI / 2);
	return (res);
}

t_ray	digital_differential_analyzer(t_map *map, float theta)
{
	t_ray	res_x;
	t_ray	res_y;

	res_x = get_dist_x(map,
			(int [2]){(int) map->pos.x, (int) map->pos.y}, theta);
	res_y = get_dist_y(map,
			(int [2]){(int) map->pos.x, (int) map->pos.y}, theta);
	if (res_x.dist < res_y.dist)
	{
		res_x.wall_side = 0;
		combine_list(res_x.dist, &res_x.object, res_y.object);
		free_list(res_y.object);
		return (res_x);
	}
	res_y.wall_side = 1;
	combine_list(res_y.dist, &res_y.object, res_x.object);
	free_list(res_x.object);
	return (res_y);
}
