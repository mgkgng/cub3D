/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 02:02:19 by min-kang          #+#    #+#             */
/*   Updated: 2022/05/03 23:25:33 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	mouse_hook(int x, int y, t_hook *hook)
{

	(void) y;
	// i should initiliase x_prev as SCREEN_X / 2
	if (x < hook->x_prev)
		hook->m_dir = -1;
	else
		hook->m_dir = 1;
	hook->m_turn = abs(hook->x_prev - x);
	hook->x_prev = x;
	hook->re = true;
	return (0);
}

int	click_hook(int mouse, t_game *game)
{
	if (mouse == 1)
	{
		(void) game;
	}
	return (0);
}