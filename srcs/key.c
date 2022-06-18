/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 01:46:41 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/17 20:48:21 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	translate(t_map *map, float theta)
{
	float	new_x;
	float	new_y;

	new_x = map->pos.x + cos(theta) * 0.1;
	new_y = map->pos.y + sin(theta) * 0.1;
	if (new_x < 0 || new_x > map->width || new_y < 0 || new_y > map->height
		|| !map->map_move[(int) new_y][(int) new_x])
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

int	key_pressed(int key, t_game *game)
{
	if (key == KEY_ESC)
		terminate(game);
	if (key == KEY_MINI)
		game->hook.minimap_on++;
	if (key == KEY_MINI_ZOOM_IN && game->hook.minimap_size > 5)
		game->hook.minimap_size--;
	if (key == KEY_MINI_ZOOM_OUT && game->hook.minimap_size < 20)
		game->hook.minimap_size++;
	if (key == KEY_UP)
		game->hook.key_flag = UP;
	else if (key == KEY_DOWN)
		game->hook.key_flag = DOWN;
	else if (key == KEY_LEFT)
		game->hook.key_flag = LEFT;
	else if (key == KEY_RIGHT)
		game->hook.key_flag = RIGHT;
	else if (key == KEY_TURN_L)
		game->hook.key_flag = TURN_L;
	else if (key == KEY_TURN_R)
		game->hook.key_flag = TURN_R;
	return (0);
}

int	key_released(int key, t_game *game)
{
	if (key == KEY_UP)
		game->hook.key_flag -= UP;
	else if (key == KEY_DOWN)
		game->hook.key_flag -= DOWN;
	else if (key == KEY_LEFT)
		game->hook.key_flag -= LEFT;
	else if (key == KEY_RIGHT)
		game->hook.key_flag -= RIGHT;
	else if (key == KEY_TURN_L)
		game->hook.key_flag -= TURN_L;
	else if (key == KEY_TURN_R)
		game->hook.key_flag -= TURN_R;
	return (0);
}

void	movement(t_game *game)
{
	if (game->hook.key_flag & UP)
		translate(&game->map, game->map.theta);
	if (game->hook.key_flag & LEFT)
		translate(&game->map, game->map.theta - M_PI / 2);
	if (game->hook.key_flag & DOWN)
		translate(&game->map, game->map.theta + M_PI);
	if (game->hook.key_flag & RIGHT)
		translate(&game->map, game->map.theta + M_PI / 2);
	if (game->hook.key_flag & TURN_L)
		turn(&game->map, -1);
	if (game->hook.key_flag & TURN_R)
		turn(&game->map, 1);
	game->hook.re = true;
}