/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:28:57 by mlecherb          #+#    #+#             */
/*   Updated: 2022/06/11 18:21:21 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	key_pressed(int key, t_game *game)
{
	printf("--%d--\n", key);
	if (key == UP)
	{
		game->key->w = 1;
	}
	if (key == DOWN)
		game->key->s = 1;
	if (key == LEFT)
		game->key->a = 1;
	if (key == RIGHT)
		game->key->d = 1;
	return (0);
}

int	key_released(int key, t_game *game)
{
	if (key == UP)
		game->key->w = 0;
	if (key == DOWN)
		game->key->s = 0;
	if (key == LEFT)
		game->key->a = 0;
	if (key == RIGHT)
		game->key->d = 0;
	return (0);
}
