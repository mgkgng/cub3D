/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 11:55:35 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/17 18:32:32 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_through(t_map map, int x, int y)
{
	if (x >= 0 && x < map.width
		&& y >= 0 && y < map.height &&  
			map.map_wall[y][x] != '1')
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

static t_raycast	get_distX(t_map map, t_point pos, int *where, float theta)
{
	t_raycast	res;
	float		deltaX;
	float		increY;
	int			side;

	res.door = NULL;
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
	while (is_through(map, res.wall.x, res.wall.y + side))
	{
		if (map.map_wall[(int) res.wall.y + side][(int) res.wall.x] == 'D') 
			ft_lstadd_front(&res.door, ft_lstnew(res.wall, perpendicular_dist(map.pos, res.wall, map.theta + PI / 2)));
		res.wall.x += deltaX;
		res.wall.y += increY;

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
	
	res.door = NULL;
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
	while (is_through(map, res.wall.x + side, res.wall.y))
	{
		if (map.map_wall[(int) res.wall.y][(int) res.wall.x + side] == 'D')
			ft_lstadd_front(&res.door, ft_lstnew(res.wall, perpendicular_dist(map.pos, res.wall, map.theta + PI / 2)));
		res.wall.x += increX;
		res.wall.y += deltaY;
	}
	res.dist = perpendicular_dist(pos, res.wall, map.theta + PI / 2);
	res.side[0] = side;
	res.side[1] = 0;
	return (res);
}

void	manip_list(t_door **one, t_door *other)
{
	t_door	*tmp;
	
	if ((*one)->dist < other->dist)
	{
		ft_lstadd_front(one, ft_lstnew(other->pos, other->dist));
		return ;
	}
	tmp = (*one)->next;
	ft_lstadd_back(one, ft_lstnew(other->pos, other->dist));
	(*one)->next->next = tmp;
}

t_door	*copy_list(t_door *lst)
{	
	t_door	*res;

	res = NULL;
	while (lst)
	{
		ft_lstadd_back(&res, ft_lstnew(lst->pos, lst->dist));
		lst = lst->next;
	}
	return (res);
}

void	get_door(float dist, t_door **origin, t_door *compare)
{
	t_door	*begin;
	t_door	*now_compare;

	begin = *origin;
	now_compare = compare;
	if (!*origin)
	{
		while (now_compare)
		{
			if (now_compare->dist < dist)
			{				
				*origin = copy_list(now_compare);
				return ;
			}
			now_compare = now_compare->next;
		}
	}
	while (now_compare)
	{
		if (now_compare->dist < dist)
		{
			while ((*origin)->next && (*origin)->next->dist > now_compare->dist)
				*origin = (*origin)->next;
			manip_list(origin, now_compare);
		}
		now_compare = now_compare->next;
	}
}

t_raycast	digital_differential_analyzer(t_map map, float theta, t_game *game)
{
	t_raycast	res_x;
	t_raycast	res_y;

	res_x = get_distX(map, map.pos, (int [2]) {(int) map.pos.x, (int) map.pos.y}, theta);
	res_y = get_distY(map, map.pos, (int [2]) {(int) map.pos.x, (int) map.pos.y}, theta);
	if (res_x.dist < res_y.dist)
	{
		game->side = 0;
		get_door(res_x.dist, &res_x.door, res_y.door);
		free_lst(res_y.door);
		return (res_x);
	}
	game->side = 1;
	get_door(res_y.dist, &res_y.door, res_x.door);
	free_lst(res_x.door);
	return (res_y);
}
