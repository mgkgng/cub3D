/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:36:02 by mlecherb          #+#    #+#             */
/*   Updated: 2022/06/16 15:45:01 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	movement(t_game *game)
{
	if (game->key->w == 1) // UP
		translate(&game->map, game->map.theta);
	if (game->key->a == 1) // LEFT
		translate(&game->map, game->map.theta - M_PI / 2);
	if (game->key->s == 1) // DOWN
		translate(&game->map, game->map.theta + M_PI);
	if (game->key->d == 1) // RIGHT
		translate(&game->map, game->map.theta + M_PI / 2);
	if (game->key->turn_l == 1)
		turn(game, &game->map, -1);
	if (game->key->turn_r == 1)
		turn(game, &game->map, 1);
	game->hook.re = true;
}