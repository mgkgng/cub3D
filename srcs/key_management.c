/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:28:57 by mlecherb          #+#    #+#             */
/*   Updated: 2022/06/17 04:19:59 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	key_pressed(int key, t_game *game)
{
	printf("--%d--\n", key);
	if (key == ESC)
		terminate(game);
	if (key == MINIMAP)
		game->hook.minimap_on++;
	if (key == MINIMAP_ZOOM_IN && game->hook.minimap_size > 5)
		game->hook.minimap_size--;
	if (key == MINIMAP_ZOOM_OUT && game->hook.minimap_size < 20)
		game->hook.minimap_size++;
	if (key == UP)
		game->key.w = 1;
	else if (key == DOWN)
		game->key.s = 1;
	else if (key == LEFT)
		game->key.a = 1;
	else if (key == RIGHT)
		game->key.d = 1;
	else if (key == TURN_L)
		game->key.turn_l = 1;
	else if (key == TURN_R)
		game->key.turn_r = 1;
	return (0);
}

int	key_released(int key, t_game *game)
{
	if (key == UP)
		game->key.w = 0;
	else if (key == DOWN)
		game->key.s = 0;
	else if (key == LEFT)
		game->key.a = 0;
	else if (key == RIGHT)
		game->key.d = 0;
	else if (key == TURN_L)
		game->key.turn_l = 0;
	else if (key == TURN_R)
		game->key.turn_r = 0;
	return (0);
}
