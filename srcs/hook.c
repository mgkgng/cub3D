/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:41:45 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/07 19:27:14 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// each time the character itself moves inside the map,
// it's actually the translation of linear function.
// i need to make a function where each time i turn the camera
// the slope should be changed, while each time the character moves,
// the intercept. 
// The problem is the vector. that means, the case where the deplacement of the characte
// is not parallel to the x y axis.
// what kind of formular could i use?
// basic formular : (x, y) coordinates will be translated into (x + cos@, y + sin@)
// so everytime the character moves into @ direction, intercept should be changed a * cos@ + sin@
// because y = ax + b formular should be transformed into y - sin@ = a * (x - cos@)
// so when the character faces the EAST, @ = 0 / SOUTH, @ = 90 / WEST, @ = 180 / NORTH, @ = 270

#include "cub3D.h"

void	translate(t_map map, t_raycast *rc)
{
	rc->intercept += rc->slope * cos(map.theta) + sin(map.theta);
}

void	turn(t_map *map, int dir)
{
	if (!dir)
		map->theta--;
	else
		map->theta++;
}