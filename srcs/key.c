/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 01:46:41 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/11 19:27:39 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

float	get_angle(float old, float change)
{
	float	res;
	res = old + change;
	if (res > M_PI * 2)
		return (res - M_PI * 2);
	else if (res < 0)
		return (res + M_PI * 2);
	return (res);
}

void	translate(t_map *map, float theta)
{
	float	new_x;
	float	new_y;

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

void	open_door(t_game *game)
{
	game->lock = 1;
	if (game->map.map2d[game->pos[1]][game->pos[0]] == true && game->min_door > 1)
		game->map.map2d[game->pos[1]][game->pos[0]] = false;
	else if (game->min_door < 2)
		game->map.map2d[game->pos[1]][game->pos[0]] = true;
}

int	key_hook(int key, t_game *game)
{
	printf("%d--\n", key);
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
	else if (key == 14) // BONUS DOOR
		open_door(game);
	else if (key == MINIMAP)
		game->hook.minimap_on++;
	else if (key == MINIMAP_ZOOM_IN && game->hook.minimap_size > 5)
		game->hook.minimap_size--;
	else if (key == MINIMAP_ZOOM_OUT && game->hook.minimap_size < 20)
		game->hook.minimap_size++;
	game->hook.re = true;
	return (0);
}
