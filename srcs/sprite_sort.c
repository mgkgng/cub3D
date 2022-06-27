/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:59:16 by mlecherb          #+#    #+#             */
/*   Updated: 2022/06/27 18:34:21 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "limits.h"

float	*sort_sprite(t_spr	*spr, t_game *game)
{
	float	*dist;
	t_spr	*tmp;
	int i;

	i = 0;
	tmp = spr;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	tmp = spr;
	dist = malloc(sizeof(float) * i);
	i = 0;
	while (tmp)
	{
		dist[i] = ((game->map.pos.x - tmp->pos.x) * (game->map.pos.x - tmp->pos.x) + (game->map.pos.y - tmp->pos.y) * (game->map.pos.y - tmp->pos.y));
		i++;
		tmp = tmp->next;
	}
	return (dist);
}

int	isAlreadyInTab(int index, int *tab, int len)
{
	int i;
	
	i = 0;
	while (i < len)
	{
		if (index == tab[i])
			return (1);
		i++;
	}
	return (0);
}

int	*sprite_order(float	*dist, int len)
{
	int i;
	int j = 0;
	int lowest = INT_MAX;
	int idx_lowest = 0;

	int	*tab = malloc(sizeof(int) * len);
	int x = 0;
	while (x++ < len)
		tab[x] = -1;
	while (j < len)
	{
		i = 0;
		lowest = INT_MAX;
		while (i < len)
		{
			if (dist[i] < lowest && isAlreadyInTab(idx_lowest, tab, j) == 0) {
				lowest = dist[i];
				idx_lowest = i;
			}
			i++;
		}
		tab[j] = idx_lowest;
		j++;
	}
}