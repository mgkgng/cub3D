/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 02:02:19 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/16 02:16:52 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <pthread.h>

int	mouse_hook(int x, int y, t_game *game)
{
	int	timeFrame;

	(void) game;
	printf("MOUSE POSITION: X - %d Y - %d\n", x, y);
	// if pthread_try works
	// thread_lock
	if (SCREEN_X - x > SCREEN_X / 3 * 2)
		timeFrame = 50000;
	else if (SCREEN_X - x > SCREEN_X / 3)
		timeFrame = 30000;
	else
		timeFrame = 10000;
	// thread_unlock
	return (0);
}

int	click_hook(int mouse, t_game *game)
{
	if (mouse == 1)
	{
		//attack
	}
	return (0);
}