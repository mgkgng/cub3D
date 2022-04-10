/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 01:46:41 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/10 23:17:28 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//** this was the note left in hook.c file (i moved translate and turn funcs here)
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
//** note end

void	translate(t_map *map, int theta)
{
	map->pos.x += cos(theta);
	map->pos.y += sin(theta);
}

void	turn(t_map *map, int dir)
{
	map->theta += dir * (M_PI_4 / 18);
	if (map->theta > M_PI * 2)
		map->theta -= M_PI * 2;
	if (map->theta < 0)
		map->theta += M_PI * 2;
}

int	key_hook(int key, t_game *game)
{
	printf("key pressed : %d\n", key);
	//printf("angle now = %d\n", game->map.theta);
	if (key == ESC)
		terminate(game);
	if (key == UP)
		game->map.pos.y--;
	else if (key == DOWN)
		game->map.pos.y++;
	else if (key == LEFT)
		game->map.pos.x--;
	else if (key == RIGHT)
		game->map.pos.x++;
	/*if (key == UP)
		translate(&game->map, game->map.theta);
	else if (key == DOWN)
		translate(&game->map, game->map.theta + M_PI_2);	
	else if (key == LEFT)
		translate(&game->map, game->map.theta + M_PI_4);
	else if (key == RIGHT)
		translate(&game->map, game->map.theta - M_PI_4);*/
	else if (key == TURN_L)
		turn(&game->map, -1);
	else if (key == TURN_R)
		turn(&game->map, 1);
	game->hook.re = true;
	return (0);
}