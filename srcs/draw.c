/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:32:18 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/12 21:31:43 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

typedef struct	s_raycast {
	t_point	wall;
	double	dist;
}

// 1. need to implement dda
// 2. need to implement raycast
// 3. need to implement the function giving the height regard of the distance between the character's point and the wall

// dda is going to return the distance

// ** should only consider the fact that north and the south (y-axis) is inverted.
// ** should also consider that fact the slope of the peripendular line of y-axis will be given as inf through atan.

double	get_distX(bool **map, t_point pos, double theta)
{
	double	h;
	double	dist;
	double	deltaX = atan(theta);
	double	deltaH = 1 / sin(theta);
	
	h = pos.y - (int) pos.y;
	if (theta > 0 && theta < M_PI_2)
		return (h / sin(theta));
	else if (theta > M_PI_2 && theta < M_PI)
		return ((1 - h) / sin(M_PI - theta));
	else
		return (-1);
	(void) map;
	(void) dist;
	return (h);
}


double	get_distY(bool **map, t_point pos, t_point case, double theta)
{
	t_raycast	res;
	double		deltaY;
	double		deltaH;
	double		increX;

	if (theta == M_PI_4 || theta == M_PI_4 * 3)
		return (-1);
	deltaY = tan(theta);
	deltaH = 1 / cos(theta);
	increX = 1;
	if ((theta < M_PI_4) || theta > M_PI_4 * 3)
		res.dist = (pos.x - case.x) / cos(theta);
	else if (theta > M_PI_4 && theta < M_PI_4 * 3)
	{
		res.dist = (pos.x - case.x) / cos(M_PI_2 - theta);
		increX *= -1;
	}
	res.wall.x = case.x + increX;
	res.wall.y = case.y + (tan(theta) * (a.pos + 1 - pos.x)) * increX;
	while (map[res.wall.x][(int) res.wall.y] == true)
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
	if (distX > distY && distX >= 0)
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