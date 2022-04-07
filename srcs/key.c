/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 01:46:41 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/06 10:55:27 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	key_hook(int key, t_gui *gui)
{
	if (key == ESC)
	{
		terminate(gui);
		exit(0);
	}
	if (key == UP) {}
	else if (key == DOWN) {}
	else if (key == LEFT) {}
	else if (key == RIGHT) {}
	else if (key == TURN_L) {}
	else if (key == TURN_R) {}
	gui->hook.re = true;
}