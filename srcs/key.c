/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 01:46:41 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/09 21:50:39 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_hook(int key, t_game *game)
{
	//printf("key pressed : %d\n", key);
	if (key == ESC)
		terminate(game);
	if (key == UP)
		translate(&game->map, game->map.theta);
	else if (key == DOWN)
		translate(&game->map, game->map.theta + 180);	
	else if (key == LEFT)
		translate(&game->map, game->map.theta + 90);
	else if (key == RIGHT)
		translate(&game->map, game->map.theta - 90);
	else if (key == TURN_L) {}
	else if (key == TURN_R) {}
	game->hook.re = true;
	return (0);
}