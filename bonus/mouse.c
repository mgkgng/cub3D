/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 02:02:19 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/18 20:42:42 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	mouse_hook(int x, int y, t_game *game)
{
	int	sensability;

	if (x < 0 || y < 0 || x > SCREEN_X || y > SCREEN_Y)
		return (1);
	sensability = abs(game->hook.x_prev - x);
	if (sensability < 3)
		return (0);
	if (x < game->hook.x_prev)
		game->hook.m_dir = -1;
	else
		game->hook.m_dir = 1;
	game->hook.x_prev = x;
	turn(&game->map, game->hook.m_dir);
	game->hook.re = true;
	return (0);
}
