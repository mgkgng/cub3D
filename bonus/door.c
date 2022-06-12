/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 18:48:28 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/12 19:19:20 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_door(t_point *door, int x, int y, int nb)
{
	int	i;

	i = -1;
	while (++i <= nb)
		if (door[i].x == x && door[i].y == y)
			return (true);
	return (false);
}

void	put_door_pos(int *x, int *y, float theta)
{
	if (theta >= PI / 4 && theta < PI * 3 / 4)
		(*y)--;
	else if (theta >= PI * 3 / 4 && theta < PI * 5 / 4)
		(*x)--;
	else if (theta >= PI * 5 / 4 && theta < PI * 7 / 4)
		(*y)++;
	else
		(*x)++;
}	

void	open_door(t_game *game)
{
	int	door_pos_x;
	int	door_pos_y;

	put_door_pos(&door_pos_x, &door_pos_y, game->map.theta);
	printf("bimbim\n");

	if (!is_door(game->map.doors, door_pos_x, door_pos_y, game->map.doors_nb))
		return ;
	printf("cocou\n");
	if (game->map.map_move[door_pos_x][door_pos_y] == false)
	{
		/* open the door */
		printf("The door is opening.\n");
		game->map.map_move[door_pos_x][door_pos_y] = true; 
	}
	else
	{
		/* close the door */
		printf("The door is closing.\n");
		game->map.map_move[door_pos_x][door_pos_y] = false;
	}
	
}