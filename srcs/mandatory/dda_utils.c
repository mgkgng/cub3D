/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:36:01 by min-kang          #+#    #+#             */
/*   Updated: 2022/07/01 15:02:44 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_m.h"

t_dda	init_dda(float theta, int xy)
{
	t_dda	res;

	if (!xy)
	{
		res.incre = 1;
		res.side = 0;
		if (theta > PI && theta < PI * 2)
		{
			res.incre = -1;
			res.side--;
		}
		res.delta = 1 / tan(theta) * res.incre;
		return (res);
	}
	res.incre = 1;
	res.side = 0;
	if (theta > PI / 2 && theta < PI / 2 * 3)
	{
		res.side--;
		res.incre = -1;
	}
	res.delta = tan(theta) * res.incre;
	return (res);
}

bool	is_through(t_map *map, int x, int y)
{
	if (x >= 0 && x < map->width && y >= 0 && y < map->height
		&& map->map_wall[y][x] != '1')
		return (true);
	return (false);
}

float	perpendicular_dist(t_point from, t_point to, float angle)
{
	float	sin_v;
	float	cos_v;

	sin_v = sin(angle);
	cos_v = cos(angle);
	return (fabs(sin_v * (to.x - from.x) - cos_v * (to.y - from.y))
		/ sqrt(pow(sin_v, 2) + pow(cos_v, 2)));
}
