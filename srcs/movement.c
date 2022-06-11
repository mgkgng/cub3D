/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:36:02 by mlecherb          #+#    #+#             */
/*   Updated: 2022/06/11 17:41:39 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	movement(t_game *game)
{
	if (game->key.w == 1) // UP
		translate(&game->map, game->map.theta);
	if (game->key.a == 1) // LEFT
		translate(&game->map, game->map.theta - M_PI / 2);
	if (game->key.s == 1) // DOWN
		translate(&game->map, game->map.theta + M_PI);
	if (game->key.d == 1) // RIGHT
		translate(&game->map, game->map.theta + M_PI / 2);
}