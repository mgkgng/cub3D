/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 01:46:41 by min-kang          #+#    #+#             */
/*   Updated: 2022/05/03 20:31:10 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	get_angle(double old, double change)
{
	double	res;
	res = old + change;
	if (res > M_PI * 2)
		return (res - M_PI * 2);
	else if (res < 0)
		return (res + M_PI * 2);
	return (res);
}

void	translate(t_map *map, double theta)
{
	//* this is wall collision
	/*if (map->map2d[(int) (map->pos.x + cos(theta) * 0.1)][(int) (map->pos.y + sin(theta) * 0.1)] == false)
		return ;*/
	printf("%f...move\n", theta);
	map->pos.x += cos(theta) * 0.1;
	map->pos.y += sin(theta) * 0.1;
}

void	turn(t_map *map, int dir)
{
	map->theta += dir * (M_PI_4 / 18);
	if (map->theta > M_PI * 2)
		map->theta -= M_PI * 2;
	if (map->theta < 0)
		map->theta += M_PI * 2;
}

int	key_hook(int key, t_game *game)
{
	if (key == ESC)
		terminate(game);
	if (key == UP)
		translate(&game->map, game->map.theta);
	else if (key == DOWN)
		translate(&game->map, game->map.theta + M_PI);	
	else if (key == LEFT)
		translate(&game->map, game->map.theta - M_PI / 2);
	else if (key == RIGHT)
		translate(&game->map, game->map.theta + M_PI / 2);
	else if (key == TURN_L)
		turn(&game->map, -1);
	else if (key == TURN_R)
		turn(&game->map, 1);
	game->hook.re = true;
	return (0);
}