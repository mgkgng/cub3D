/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 11:55:35 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/14 20:56:20 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static float	perpendicular_dist(t_point from, t_point to, float angle)
{
	float	sin_v;
	float	cos_v;

	sin_v = sin(angle);
	cos_v = cos(angle);
	return (fabs(sin_v * (to.x - from.x) - cos_v * (to.y - from.y))
		/ sqrt(pow(sin_v, 2) + pow(cos_v, 2)));
}

static void	put_door(t_door *door, t_point from, t_point to, float angle)
{
	if (!door->nb)
	{
		door->pos = malloc(sizeof(t_point));
		door->dist = malloc(sizeof(float));
	}
	else
	{
		door->pos = ft_realloc(door->pos, sizeof(t_point) * (door->nb + 1));
		door->dist = ft_realloc(door->pos, sizeof(float) * (door->nb + 1));
	}
	door->pos[door->nb].x = to.x;
	door->pos[door->nb].y = to.y;
	door->dist[door->nb++] = perpendicular_dist(from, to, angle);
}

static t_raycast	get_distX(t_map map, t_point pos, int *where, float theta)
{
	t_raycast	res;
	float		deltaX;
	float		increY;
	int			side;

	res.dist = INT32_MAX;
	if (!theta || theta == PI)
		return (res);
	increY = 1;
	side = 0;
	if (theta > 0 && theta < PI)
		where[1]++;
	else
	{
		increY = -1;
		side--;
	}
	deltaX = 1 / tan(theta) * increY;
	res.wall.x = pos.x + (where[1] - pos.y) / tan(theta);
	res.wall.y = where[1];
	while (res.wall.x >= 0 && res.wall.x < map.width
		&& map.map_wall[(int) res.wall.y + side][(int) res.wall.x] != '1')
	{
		res.wall.x += deltaX;
		res.wall.y += increY;
		if (map.map_wall[(int) res.wall.y + side][(int) res.wall.x] == 'D')
			put_door(&res.door, pos, res.wall, map.theta + PI / 2);
	}
	res.dist = perpendicular_dist(pos, res.wall, map.theta + PI / 2);
	res.side[1] = side;
	res.side[0] = 0;
	return (res);
}

static t_raycast	get_distY(t_map map, t_point pos, int *where, float theta)
{
	t_raycast	res;
	float		deltaY;
	float		increX;
	int			side;
	
	res.dist = INT32_MAX;
	if (theta == PI / 2 || theta == PI / 2 * 3)
		return (res);
	increX = 1;
	side = 0;
	if (theta > PI / 2 && theta < PI / 2 * 3)
	{
		side--;
		increX = -1;
	}
	else
		where[0]++;
	deltaY = tan(theta) * increX;
	res.wall.x = where[0];
	res.wall.y = pos.y + (where[0] - pos.x) * tan(theta);
	while (res.wall.y >= 0 && res.wall.y < map.height
		&& map.map_wall[(int) res.wall.y][(int) res.wall.x + side] != '1')
	{
		res.wall.x += increX;
		res.wall.y += deltaY;
		if (map.map_wall[(int) res.wall.y][(int) res.wall.x + side] == 'D')
			put_door(&res.door, pos, res.wall, map.theta + PI / 2);
	}
	res.dist = perpendicular_dist(pos, res.wall, map.theta + PI / 2);
	res.side[0] = side;
	res.side[1] = 0;
	return (res);
}

t_raycast	digital_differential_analyzer(t_map map, float theta)
{
	t_raycast	res_x;
	t_raycast	res_y;

	res_x = get_distX(map, map.pos, (int [2]) {(int) map.pos.x, (int) map.pos.y}, theta);
	res_y = get_distY(map, map.pos, (int [2]) {(int) map.pos.x, (int) map.pos.y}, theta);
	if (res_x.dist < res_y.dist)
		return (res_x);
	return (res_y);
}
