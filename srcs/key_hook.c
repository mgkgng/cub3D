/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 15:59:43 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/18 15:59:43 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
