/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 02:02:19 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/17 17:46:01 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	mouse_hook(int x, int y, t_game *game)
{
	//int	timeFrame;
	double	turnDegree;
	int		i;
	int		dir;

	(void) game;
	(void) y;
	//printf("MOUSE POSITION: X - %d Y - %d\n", x, y);
	// if pthread_try works
	// thread_lock
	turnDegree = 0;
	if (x < SCREEN_X / 2)
		dir = -1;
	else
		dir = 1;
	if (SCREEN_X - x > SCREEN_X / 3 * 2)
		turnDegree = 10;
	else if (SCREEN_X - x > SCREEN_X / 3)
		turnDegree = 5;
	/*else
		timeFrame = 10000;*/
	i = -1;
	while (++i < turnDegree)
	{
		turn(&game->map, dir);
	}
	game->hook.re = true;
	// thread_unlock
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