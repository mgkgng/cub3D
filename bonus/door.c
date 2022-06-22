/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 18:48:28 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/20 12:18:51 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_door_pos(t_point *pos, float theta)
{
	if (theta >= PI / 4 && theta < PI * 3 / 4)
		pos->y++;
	else if (theta >= PI * 3 / 4 && theta < PI * 5 / 4)
		pos->x--;
	else if (theta >= PI * 5 / 4 && theta < PI * 7 / 4)
		pos->y--;
	else
		pos->x++;
}	

void	open_door(t_game *game)
{
	t_point	door_pos;

	door_pos.x = game->map.pos.x;
	door_pos.y = game->map.pos.y;
	put_door_pos(&door_pos, game->map.theta);
	if (game->map.map_wall[(int) door_pos.y][(int) door_pos.x] != 'D')
		return ;
	if (game->map.map_move[(int) door_pos.y][(int) door_pos.x] == false)
		game->map.map_move[(int) door_pos.y][(int) door_pos.x] = true;
	else
		game->map.map_move[(int) door_pos.y][(int) door_pos.x] = false;
}
