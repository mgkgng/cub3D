/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 02:02:19 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/22 21:12:48 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_hook(int x, int y, t_game *game)
{
	int	sensability;

	if (x < 0 || y < 0 || x > SCREEN_X || y > SCREEN_Y)
		return (1);
	sensability = abs(game->hook.mouse_x_prev - x);
	if (sensability < 2)
		return (0);
	if (x < game->hook.mouse_x_prev && !(game->hook.flag & MOUSE_L))
		game->hook.flag += MOUSE_L;
	else if (x > game->hook.mouse_x_prev && !(game->hook.flag & MOUSE_R))
		game->hook.flag += MOUSE_R;
	game->hook.mouse_x_prev = x;
	return (0);
}
