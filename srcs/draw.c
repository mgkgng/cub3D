/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:32:18 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/13 17:43:39 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

typedef struct	s_raycast {
	t_point	wall;
	double	dist;
}	t_raycast;

// 1. need to implement dda
// 2. need to implement raycast
// 3. need to implement the function giving the height regard of the distance between the character's point and the wall

// dda is going to return the distance

// ** should only consider the fact that north and the south (y-axis) is inverted.
// ** should also consider that fact the slope of the peripendular line of y-axis will be given as inf through atan.

t_raycast	get_distX(bool **map, t_point pos, int *case, double theta)
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
	{
		deltaX = 1 / tan(theta);
		res.dist = (case[1] + 1 - pos.y) / sin(theta);
		res.wall.x = pos.x + (case[1] + 1 - pos.y) / tan(theta);
		res.wall.y = case[1] + increY;
	}
	else if (theta > M_PI && theta < M_PI * 2)
	{
		increY = -1;
		deltaX = 1 / tan(theta - M_PI_2) * increY;
		res.dist = (pos.y - case[1]) * sin(theta - M_PI);
		res.wall.x = pos.x + (pos.y - case[1]) / tan(theta) * increY;
		res.wall.y = case[1];
	}
	while (map[(int) res.wall.x][(int) res.wall.y] == true)
	{
		res.dist += deltaH;
		res.wall.x += deltaX;
		res.wall.y += increY;
	}
	return (res);
}


t_raycast	get_distY(bool **map, t_point pos, int *case, double theta)
{
	t_raycast	res;
	double		deltaY;
	double		deltaH;
	double		increX;

	res.dist = 0;
	if (theta == M_PI_2 || theta == M_PI_2 * 3)
		return (res);
	deltaY = tan(theta);
	deltaH = 1 / cos(theta);
	increX = 1;
	if (theta > M_PI_2 && theta < M_PI_2 * 3)
		increX *= -1;
	res.dist = (pos.x - case[0]) / cos(theta) * increX;
	res.wall.x = case[0] + increX;
	res.wall.y = case[1] + (tan(theta) * (a.pos + 1 - pos.x)) * increX;
	while (map[(int) res.wall.x][(int) res.wall.y] == true)
	{
		res.dist += deltaH;
		res.wall.x += increX;
		res.wall.y += deltaY * increX;
	}
	return (res);
}

/*int	digital_differential_analyzer(t_point pos, char **map, int theta)
{
	double	distX;
	double	distY;
	double	dist;

	distX = get_distX(map, pos, theta);
	distY = get_distY(map, pos, theta);
	if (distX && distX > distY)
		dist = distX;
	else
		dist = distY;
}*/

/*void	raycast(t_point pos, char **map, int theta)
{
	// ça c'est une idee geniale ;)
	t_point	dir;
	double	dist;

	dir.x = pos.x + cos(theta);
	dir.y = pos.y + sin(theta);
	dist = digital_differential_analyzer(pos, dir, map, theta);
	// need height/distance calculator here
}

int draw(t_map map, t_raycast rc)
{
	int	i;

	i = -1;
	while (++i < ANGLE / 2)
	{
		// left
		raycast(map.pos, map.map2d, map.theta - i);
		// right 
		raycast(map.pos, map.map2d, map.theta + i);
	}
}*/