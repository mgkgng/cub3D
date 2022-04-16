/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 01:46:41 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/16 14:50:22 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	translate(t_map *map, int theta)
{
	if (map->map2d[(int) (map->pos.y + cos(theta) * 0.1)][(int) (map->pos.x + sin(theta) * 0.1)] == false)
		return ;
	map->pos.x += cos(theta) * 0.1;
	map->pos.y += sin(theta) * 0.1;
}

void	turn(t_map *map, int dir)
{
	map->theta += dir * (M_PI_4 / 45);
	if (map->theta > M_PI * 2)
		map->theta -= M_PI * 2;
	if (map->theta < 0)
		map->theta += M_PI * 2;
}

int	key_hook(int key, t_game *game)
{
	printf("key pressed : %d\n", key);
	//printf("angle now = %d\n", game->map.theta);
	if (key == ESC)
		terminate(game);
	if (key == UP)
		translate(&game->map, game->map.theta);
	else if (key == DOWN)
		translate(&game->map, game->map.theta + M_PI);	
	else if (key == LEFT)
		translate(&game->map, game->map.theta + M_PI_2);
	else if (key == RIGHT)
		translate(&game->map, game->map.theta - M_PI_2);
	else if (key == TURN_L)
		turn(&game->map, 1);
	else if (key == TURN_R)
		turn(&game->map, -1);
	game->hook.re = true;
	return (0);
}