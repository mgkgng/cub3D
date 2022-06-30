/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:39:39 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/30 22:48:24 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_m.h"

int	key_pressed(int key, t_game *game)
{
	if (key == KEY_ESC)
		terminate(game);
	else if (key == KEY_UP && !(game->hook.flag & UP))
		game->hook.flag += UP;
	else if (key == KEY_DOWN && !(game->hook.flag & DOWN))
		game->hook.flag += DOWN;
	else if (key == KEY_LEFT && !(game->hook.flag & LEFT))
		game->hook.flag += LEFT;
	else if (key == KEY_RIGHT && !(game->hook.flag & RIGHT))
		game->hook.flag += RIGHT;
	else if (key == KEY_TURN_L && !(game->hook.flag & TURN_L))
		game->hook.flag += TURN_L;
	else if (key == KEY_TURN_R && !(game->hook.flag & TURN_R))
		game->hook.flag += TURN_R;
	return (0);
}

int	key_released(int key, t_game *game)
{
	if (key == KEY_UP)
		game->hook.flag -= UP;
	else if (key == KEY_DOWN)
		game->hook.flag -= DOWN;
	else if (key == KEY_LEFT)
		game->hook.flag -= LEFT;
	else if (key == KEY_RIGHT)
		game->hook.flag -= RIGHT;
	else if (key == KEY_TURN_L)
		game->hook.flag -= TURN_L;
	else if (key == KEY_TURN_R)
		game->hook.flag -= TURN_R;
	return (0);
}