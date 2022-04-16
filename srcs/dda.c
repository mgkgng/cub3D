/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 11:55:35 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/16 14:53:40 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// ** should only consider the fact that north and the south (y-axis) is inverted.

t_raycast	get_distX(t_map map, t_point pos, int *where, double theta)
{
	t_raycast	res;
	double		deltaX;
	double		deltaH;
	double		increY;

	res.dist = 0;
	if (!theta || theta == M_PI)
		return (res);
	deltaH = 1 / sin(theta);
	increY = 1;
	if (theta > 0 && theta < M_PI)
		where[1]++;
	else
		increY = -1;
	printf("x====%f\n", res.wall.x);
	printf("y====%f\n", res.wall.y);
	deltaX = 1 / tan(theta) * increY;
	res.dist = (where[1] - pos.y) / sin(theta);
	res.wall.x = pos.x + (where[1] - pos.y) / tan(theta);
	res.wall.y = where[1];
	printf("rrreess wallx === %f, wally=== %f\n", res.wall.x, res.wall.y);
	while (res.wall.x < map.width && map.map2d[(int) res.wall.y][(int) res.wall.x])
	{
		res.dist += deltaH;
		res.wall.x += deltaX;
		res.wall.y += increY;
	}
	return (res);
}

/*static t_raycast	get_distX(bool **map, t_point pos, int *where, double theta)
{
	t_raycast	res;
	double		deltaX;
	double		deltaH;
	double		increY;

	res.dist = 0;
	if (!theta || theta == M_PI)
		return (res);
	deltaH = 1 / sin(theta);
	increY = 1;
	printf("yoooo xxxx == %f y ==== %f\n", pos.x, pos.y);
	printf("wwwhhheeerre xx==%d, y == %d\n", where[0], where[1]);
	printf("angle --> %f\n", theta);
	if (theta > 0 && theta < M_PI)
	{
		pos.y += 1;
		res.wall.y = where[1] + 1;
	}
	else if (theta > M_PI && theta < M_PI * 2)
	{
		increY = -1;
		res.wall.y = where[1];
	}
	deltaX = 1 / tan(theta) * increY;
	res.dist = (where[1] - pos.y) / sin(theta);
	res.wall.x = pos.x + (where[1] - pos.y) / tan(theta);
	printf("x====%f\n", res.wall.x);
	printf("y====%f\n", res.wall.y);
	while (map[(int) res.wall.x][(int) res.wall.y] == true)
	{

		res.dist += deltaH;
		res.wall.x += deltaX;
		res.wall.y += increY;
	}
	return (res);
}*/

static t_raycast	get_distY(t_map map, t_point pos, int *where, double theta)
{
	t_raycast	res;
	double		deltaY;
	double		deltaH;
	double		increX;

	res.dist = 0;
	if (theta == M_PI_2 || theta == M_PI_2 * 3)
		return (res);
	deltaH = 1 / cos(theta);
	increX = 1;

	if (theta > M_PI_2 && theta < M_PI_2 * 3)
		increX *= -1;
	else
		where[0]++;
	deltaY = tan(theta) * increX;
	res.dist = (where[0] - pos.x) / cos(theta);
	res.wall.x = where[0];
	res.wall.y = pos.y + (where[0] - pos.x) * tan(theta);
	while (res.wall.y < map.height && map.map2d[(int) res.wall.y][(int) res.wall.x])
	{
		res.dist += deltaH;
		res.wall.x += increX;
		res.wall.y += deltaY;
		printf("BOUXBOUC wallx === %f, wally=== %f\n", res.wall.x, res.wall.y);
	}
	return (res);
}

t_raycast	digital_differential_analyzer(t_map map, double theta)
{
	t_raycast	resX;
	t_raycast	resY;

	resX = get_distX(map, map.pos, (int [2]) {(int) map.pos.x, (int) map.pos.y}, theta);
	resY = get_distY(map, map.pos, (int [2]) {(int) map.pos.x, (int) map.pos.y}, theta);
	if (resX.dist && resX.dist < resY.dist)
		return (resX);
	return (resY);
}