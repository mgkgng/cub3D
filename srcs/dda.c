/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 11:55:35 by min-kang          #+#    #+#             */
/*   Updated: 2022/05/03 21:21:20 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//* to do list
//* 1. anti fisheye distortion
//* 2. 0 height at 90 degree
//* 3. seg fault when out of the wall 

static t_raycast	get_distX(t_map map, t_point pos, int *where, double theta)
{
	t_raycast	res;
	double		deltaX;
	double		deltaH;
	double		increY;
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
	deltaH = 1 / sin(theta) * increY;
	deltaX = 1 / tan(theta) * increY;
	res.dist = (where[1] - pos.y) / sin(theta);
	res.wall.x = pos.x + (where[1] - pos.y) / tan(theta);
	res.wall.y = where[1];
	while (res.wall.x >= 0 && res.wall.x < map.width
		&& map.map2d[(int) res.wall.y + side][(int) res.wall.x])
	{
		res.dist += deltaH;
		res.wall.x += deltaX;
		res.wall.y += increY;
	}
	return (res);
}

static t_raycast	get_distY(t_map map, t_point pos, int *where, double theta)
{
	t_raycast	res;
	double		deltaY;
	double		deltaH;
	double		increX;
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
	deltaH = 1 / cos(theta) * increX;
	deltaY = tan(theta) * increX;
	res.dist = (where[0] - pos.x) / cos(theta);
	res.wall.x = where[0];
	res.wall.y = pos.y + (where[0] - pos.x) * tan(theta);
	while (res.wall.y >= 0 && res.wall.y < map.height
		&& map.map2d[(int) res.wall.y][(int) res.wall.x + side])
	{
		res.dist += deltaH;
		res.wall.x += increX;
		res.wall.y += deltaY;
	}
	return (res);
}

t_raycast	digital_differential_analyzer(t_map map, double theta)
{
	t_raycast	res_x;
	t_raycast	res_y;

	res_x = get_distX(map, map.pos, (int [2]) {(int) map.pos.x, (int) map.pos.y}, theta);
	res_y = get_distY(map, map.pos, (int [2]) {(int) map.pos.x, (int) map.pos.y}, theta);
	if (res_x.dist < res_y.dist)
		return (res_x);
	return (res_y);
}