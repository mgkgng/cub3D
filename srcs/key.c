/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 01:46:41 by min-kang          #+#    #+#             */
/*   Updated: 2022/05/05 17:09:58 by min-kang         ###   ########.fr       */
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
	double	new_x;
	double	new_y;

	new_x = map->pos.x + cos(theta) * 0.1;
	new_y = map->pos.y + sin(theta) * 0.1;
	if (new_x < 0 || new_x > map->width || new_y < 0 || new_y > map->height
		|| !map->map2d[(int) new_y][(int) new_x])
		return ;
	map->pos.x = new_x;
	map->pos.y = new_y;
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
	//printf("%d--\n", key);
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
	//* bonus
	else if (key == MINIMAP)
		game->hook.minimap_on++;
	game->hook.re = true;
	return (0);
}