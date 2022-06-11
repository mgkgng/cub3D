/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 11:55:35 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/11 13:26:32 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float	perpendicular_dist(float *from, float *to, float angle)
{
	float	sin_v;
	float	cos_v;

	sin_v = sin(angle);
	cos_v = cos(angle);
	return (fabs(sin_v * (to[0] - from[0]) - cos_v * (to[1] - from[1]))
		/ sqrt(pow(sin_v, 2) + pow(cos_v, 2)));
}

static t_raycast	get_distX(t_map map, t_point pos, int *where, float theta, t_game *game)
{
	t_raycast	res;
	float		deltaX;
	float		increY;
	int			side;
	(void)game;

	res.dist =INT32_MAX;
	res.verif = 0;
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
		&& map.map2d[(int) res.wall.y + side][(int) res.wall.x])
	{
		// if (game->mapi[(int) res.wall.y][(int) res.wall.x] == '2')
			// printf("DOOR : %c\n", game->mapi[(int) res.wall.y][(int) res.wall.x]);
		res.wall.x += deltaX;
		res.wall.y += increY;
		// if (is_door(game->door, (int) res.wall.x, (int) res.wall.y, game))
		// {
		// 	game->min_door = perpendicular_dist((float [2]) {pos.x, pos.y}, (float [2]) {res.wall.x, res.wall.y}, map.theta + PI / 2);
		// 	game->pos[0] = res.wall.x;
		// 	game->pos[1] = res.wall.y;
		// 	res.verif = 1;
		// }
	}
	res.dist = perpendicular_dist((float [2]) {pos.x, pos.y}, (float [2]) {res.wall.x, res.wall.y}, map.theta + PI / 2);
	return (res);
}

static t_raycast	get_distY(t_map map, t_point pos, int *where, float theta, t_game *game)
{
	t_raycast	res;
	float		deltaY;
	float		increX;
	int			side;
	(void)game;
	
	res.verif = 0;
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
		&& map.map2d[(int) res.wall.y][(int) res.wall.x + side])
	{
		// if (game->mapi[(int) res.wall.y][(int) res.wall.x] == '2')
			// printf("DOOR : %c\n", game->mapi[(int) res.wall.y][(int) res.wall.x]);
		res.wall.x += increX;
		res.wall.y += deltaY;
		// if (is_door(game->door, (int) res.wall.x, (int) res.wall.y, game))
		// {
		// 	game->min_door = perpendicular_dist((float [2]) {pos.x, pos.y}, (float [2]) {res.wall.x, res.wall.y}, map.theta + PI / 2);
		// 	game->pos[0] = res.wall.x;
		// 	game->pos[1] = res.wall.y;
		// 	res.verif = 1;
		// }
	}
	res.dist = perpendicular_dist((float [2]) {pos.x, pos.y}, (float [2]) {res.wall.x, res.wall.y}, map.theta + PI / 2);
	return (res);
}

t_raycast	digital_differential_analyzer(t_map map, float theta, t_game *game)
{
	t_raycast	res_x;
	t_raycast	res_y;

	res_x = get_distX(map, map.pos, (int [2]) {(int) map.pos.x, (int) map.pos.y}, theta, game);
	res_y = get_distY(map, map.pos, (int [2]) {(int) map.pos.x, (int) map.pos.y}, theta, game);
	if (res_x.dist < res_y.dist)
		return (res_x);
	return (res_y);
}
