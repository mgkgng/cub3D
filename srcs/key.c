/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 15:59:43 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/20 12:18:18 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_pressed(int key, t_game *game)
{
	if (key == KEY_ESC)
		terminate(game);
	else if (key == KEY_MINI)
		game->hook.minimap_on++;
	else if (key == KEY_MINI_ZOOM_IN && game->hook.minimap_size > 5)
		game->hook.minimap_size--;
	else if (key == KEY_MINI_ZOOM_OUT && game->hook.minimap_size < 20)
		game->hook.minimap_size++;
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
	else if (key == KEY_DOOR)
		open_door(game);
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
